/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:05:45 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/22 17:37:22 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	do_pipes(t_command_list *cmd_lst, t_pipe *pipes)
{
	if (cmd_lst->next)
	{
		pipes->open = 1;
		pipe(pipes->fd);
		fprintf(stderr, "Created pipe r:%d w:%d\n", pipes->fd[0], pipes->fd[1]);
		if (cmd_lst->out_fd == -1)
		{
			fprintf(stderr, "write to pipefd %d\n", pipes->fd[1]);
			cmd_lst->out_fd = pipes->fd[1];
		}
	}
	if (cmd_lst->in_fd == -1 && pipes->next->open == 1)
	{
		fprintf(stderr, "read from pipfd %d\n", pipes->next->fd[0]);
		cmd_lst->in_fd = pipes->next->fd[0];
	}
	return (0);
}

int	assign_fds(int in_fd, int out_fd, int stdin, int stdout)
{
	fprintf(stderr, "assign in: %d out: %d\n", in_fd, out_fd);
	if (in_fd != -1)
	{
		fprintf(stderr, "duping STDIN to %d\n", in_fd);
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	else
	{
		in_fd = stdin;
		fprintf(stderr, "No in_fd; in_fd: %d\n", in_fd);
	}
	if (out_fd != -1)
	{
		fprintf(stderr, "duping STDOUT to %d\n", out_fd);
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	else
	{
		out_fd = stdout;
		fprintf(stderr, "No outr_fd; out_fd: %d\n", out_fd);
	}
	return (0);
}

int	check_fds(t_data *data, t_command_list *cmd_lst, t_pipe *pipes)
{
	int	i;

	fprintf(stderr, "*********Checking fds for command %s********\n",
		cmd_lst->arg->token);
	i = 0;
	while (cmd_lst->arg[i].token != NULL)
	{
		if (cmd_lst->next || pipes->next->open)
			do_pipes(cmd_lst, pipes);
		if (cmd_lst->arg[i].type == IN)
			if (open_file(&cmd_lst->in_fd, cmd_lst->arg[i].token, O_RDONLY, 0))
				return (print_file_error("minishell: ", cmd_lst->arg[i].token));
		if (cmd_lst->arg[i].type == OUT)
			if (open_file(&cmd_lst->out_fd, cmd_lst->arg[i].token,
					O_CREAT | O_WRONLY | O_TRUNC, 0664))
				return (print_file_error("minishell: ", cmd_lst->arg[i].token));
		if (cmd_lst->arg[i].type == APPEND)
			if (open_file(&cmd_lst->out_fd, cmd_lst->arg[i].token,
					O_CREAT | O_WRONLY | O_APPEND, 0664))
				return (print_file_error("minishell: ", cmd_lst->arg[i].token));
		if (cmd_lst->arg[i].type == HEREDOC)
		{
			if (mini_heredoc(data, cmd_lst->arg[i].token))
				return (print_file_error("minishell: ", "heredoc"));
			cmd_lst->in_fd = open("heredoc_163465", O_RDONLY);
		}
		i++;
	}
	assign_fds(cmd_lst->in_fd, cmd_lst->out_fd, cmd_lst->stdin,
		cmd_lst->stdout);
	fprintf(stderr, "in check_fds: in %d out %d\n", cmd_lst->in_fd, cmd_lst->out_fd);
	return (0);
}

int	execute_execve(t_command_list *cmd_lst, char **args, t_pipe *pipes)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("minishell: error forking\n", 2);
		return (-1);
	}
	if (pipes->open)
	{
		fprintf(stderr, "closing %d\n", pipes->fd[1]);
		close(pipes->fd[1]);
	}
	if (pid == 0)
	{
		fprintf(stderr, "Child\n");
		// fprintf(stderr, "ch reading from %d\n", cmd_lst->in_fd);
		// fprintf(stderr, "ch writing to %d\n", cmd_lst->out_fd);
		if (execve(cmd_lst->exec_path, args, NULL) == -1)
		{
			if (cmd_lst->in_fd != -1)
				close(cmd_lst->in_fd);
			if (cmd_lst->out_fd != -1)
				close(cmd_lst->out_fd);
			dup2(cmd_lst->stdin, STDIN_FILENO);
			dup2(cmd_lst->stdout, STDOUT_FILENO);
			close(cmd_lst->stdin);
			close(cmd_lst->stdout);
			ft_putstr_fd(cmd_lst->arg->token, 2);
			ft_putendl_fd(": command not found", 2);
			exit(127);
		}
	}
	return (0);
}

int	check_cmd(t_data *data, t_command_list *cmd_lst, t_pipe *pipes)
{
	char	**arg_list;
	int		no_of_forks;
	int		status;

	no_of_forks = 0;
	data->pipes.open = 0;
	data->pipes.next->open = 0;
	while (cmd_lst)
	{
		cmd_lst->out_fd = -1;
		cmd_lst->in_fd = -1;
		cmd_lst->stdin = dup(STDIN_FILENO);
		cmd_lst->stdout = dup(STDOUT_FILENO);
		check_path(data->path, cmd_lst);
		fprintf(stderr, "original stding: %d, stdout %d\n", cmd_lst->stdin,
			cmd_lst->stdout);
		arg_list = get_arg_list(cmd_lst->arg);
		if (check_fds(data, cmd_lst, pipes))
		{
			if (data->heredoc)
				unlink("heredoc_163465");
			free(arg_list);
			revert_fds(cmd_lst);
		}
		fprintf(stderr, "******Executing command: %s******\n", *arg_list);
		// if (is_builtin(cmd_lst->exec_name))
		//     data->exit_status = execute_builtin(cmd_lst);
		// else
		fprintf(stderr, "in check_cmd: in %d out %d\n", cmd_lst->in_fd, cmd_lst->out_fd);
		if (!execute_execve(cmd_lst, arg_list, pipes))
			no_of_forks++;
		if (pipes->next->open)
		{
			fprintf(stderr, "closing pipes %d and %d\n", pipes->next->fd[0],
				pipes->next->fd[1]);
			close(pipes->next->fd[0]);
			// close(pipes->next->fd[1]);
		}
		pipes = pipes->next;
		free(arg_list);
		revert_fds(cmd_lst);
		cmd_lst = cmd_lst->next;
	}
	while (no_of_forks--)
		waitpid(-1, &status, 0);
	data->exit_status = WEXITSTATUS(status);
	fprintf(stderr, "EXIT STATUS: %d\n", data->exit_status);
	return (WEXITSTATUS(status));
	// return (0);
}

// int main(void)
// {
// 	t_command_list *cmd_lst = (t_command_list *)malloc(sizeof(t_command_list));
// 	t_command_list *temp = cmd_lst;
// 	cmd_lst->exec_path = "/usr/bin/ls";
// 	cmd_lst->arg = malloc(sizeof(t_arg));
// 	cmd_lst->next = NULL;
// 	cmd_lst->in_fd = -1;
// 	cmd_lst->out_fd = -1;
// 	t_arg *arg = cmd_lst->arg;
// 	arg->token = "ls";
// 	arg->type = STR;
// 	// arg->next = malloc(sizeof(t_arg));
// 	// arg = arg->next;
// 	// arg->token = "-c";
// 	// arg->type = STR;
// 	arg->next = malloc(sizeof(t_arg));
// 	arg = arg->next;
// 	arg->token = "file1";
// 	arg->type = IN;
// 	arg->next = malloc(sizeof(t_arg));
// 	arg = arg->next;
// 	arg->token = "file56";
// 	arg->type = PIPE;
// 	// arg->next = malloc(sizeof(t_arg));
// 	// arg = arg->next;
// 	// arg->token = "file4";
// 	// arg->type = 2;
// 	arg->next = NULL;

// 	cmd_lst->next = (t_command_list *)malloc(sizeof(t_command_list));
// 	cmd_lst = cmd_lst->next;
// 	cmd_lst->exec_path = "/usr/bin/grep";
// 	cmd_lst->arg = malloc(sizeof(t_arg));
// 	cmd_lst->next = NULL;
// 	cmd_lst->in_fd = -1;
// 	cmd_lst->out_fd = -1;
// 	t_arg *arg2 = cmd_lst->arg;
// 	arg2->token = "grep";
// 	arg2->type = STR;
// 	arg2->next = malloc(sizeof(t_arg));
// 	arg2 = arg2->next;
// 	arg2->token = "u";
// 	arg2->type = STR;
// 	// arg2->next = malloc(sizeof(t_arg));
// 	// arg2 = arg2->next;
// 	// arg2->token = "file44";
// 	// arg2->type = OUT;
// 	arg2->next = malloc(sizeof(t_arg));
// 	arg2 = arg2->next;
// 	arg2->token = "echo result";
// 	arg2->type = PIPE;
// 	// arg2->next = malloc(sizeof(t_arg));
// 	// arg2 = arg2->next;
// 	// arg2->token = "file4";
// 	// arg2->type = 2;
// 	arg2->next = NULL;

// 	cmd_lst->next = (t_command_list *)malloc(sizeof(t_command_list));
// 	cmd_lst = cmd_lst->next;
// 	cmd_lst->exec_path = "/usr/bin/grep";
// 	cmd_lst->arg = malloc(sizeof(t_arg));
// 	cmd_lst->next = NULL;
// 	cmd_lst->in_fd = -1;
// 	cmd_lst->out_fd = -1;
// 	// t_arg *arg3 = cmd_lst->arg;
// 	// arg3->token = "grep";
// 	// arg3->type = STR;
// 	// arg3->next = malloc(sizeof(t_arg));
// 	// arg3 = arg3->next;
// 	// arg3->token = "lu";
// 	// arg3->type = STR;
// 	// // arg3->next = malloc(sizeof(t_arg));
// 	// // arg3 = arg3->next;
// 	// // arg3->token = "file44";
// 	// // arg3->type = OUT;
// 	// arg3->next = malloc(sizeof(t_arg));
// 	// arg3 = arg3->next;
// 	// arg3->token = "echo result";
// 	arg3->type = HEREDOC;
// 	arg3->next = NULL;

// 	cmd_lst->next = (t_command_list *)malloc(sizeof(t_command_list));
// 	cmd_lst = cmd_lst->next;
// 	cmd_lst->exec_path = "/usr/bin/wc";
// 	cmd_lst->arg = malloc(sizeof(t_arg));
// 	cmd_lst->next = NULL;
// 	cmd_lst->in_fd = -1;
// 	cmd_lst->out_fd = -1;
// 	t_arg *arg4 = cmd_lst->arg;
// 	arg4->token = "wc";
// 	arg4->type = STR;
// 	// arg4->next = malloc(sizeof(t_arg));
// 	// arg4 = arg4->next;
// 	// arg4->token = "24";
// 	// arg4->type = STR;
// 	arg4->next = malloc(sizeof(t_arg));
// 	arg4 = arg4->next;
// 	arg4->token = "file";
// 	arg4->type = END;
// 	arg4->next = NULL;
// 	cmd_lst->next = NULL;

// 	check_cmd(temp, &data.pipes);
// 	while (cmd_lst)
// 	{
// 		t_command_list *temp_c = cmd_lst;
// 		while (cmd_lst->arg)
// 		{
// 			t_arg *temp = cmd_lst->arg;
// 			cmd_lst->arg = cmd_lst->arg->next;
// 			free(temp);
// 		}
// 		cmd_lst = cmd_lst->next;
// 		free(temp_c);
// 	}
// }