/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:05:45 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/19 21:22:55 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_arg_list(t_arg *arg)
{
	int		len;
	int		i;
	t_arg	*temp;
	char	**arg_list;

	temp = arg;
	len = 0;
	while (temp)
	{
		if (temp->type == 0)
			len++;
		temp = temp->next;
	}
	arg_list = (char **)ft_calloc(len + 1, sizeof(char *));
	i = 0;
	temp = arg;
	while (temp)
	{
		if (temp->type == 0)
			arg_list[i++] = temp->token;
		temp = temp->next;
	}
	return (arg_list);
}

int	open_file(int *fd, char *filename, int flags, int perms)
{
	if (*fd != -1)
		close(*fd);
	*fd = open(filename, flags | O_CLOEXEC, perms);
	if (*fd == -1)
		return (1);
	return (0);
}

int	do_pipes(t_command_list *cmd_lst, t_pipe *pipes)
{
	close(pipes->fd[0]);
	if (cmd_lst->out_fd == -1)
	{
		printf("write to %d\n", pipes->next->fd[1]);
		cmd_lst->out_fd = pipes->fd[1];
	}
	// if (cmd_lst->in_fd == -1)
	// {
	// 	printf("read from %d\n", pipes->next->fd[0]);
	// 	cmd_lst->in_fd = pipes->next->fd[0];
	// }
	pipes->open = 1;
	pipes = pipes->next;
	return (0);
}

int	check_fds(t_command_list *cmd_lst, t_pipe *pipes)
{
	t_arg	*temp;

	temp = cmd_lst->arg;
	while (temp)
	{
		if (temp->type == IN)
			if (open_file(&cmd_lst->in_fd, temp->token, O_RDONLY, 0))
				return (print_file_error("minishell: ", temp->token));
		if (temp->type == OUT)
			if (open_file(&cmd_lst->out_fd, temp->token,
					O_CREAT | O_WRONLY | O_TRUNC, 0664))
				return (print_file_error("minishell: ", temp->token));
		if (temp->type == APPEND)
			if (open_file(&cmd_lst->out_fd, temp->token,
					O_CREAT | O_WRONLY | O_APPEND, 0664))
				return (print_file_error("minishell: ", temp->token));
		if (temp->type == HEREDOC)
			if (open_file(&cmd_lst->out_fd, "/tmp/here_doc234097",
					O_CREAT | O_RDWR | O_TRUNC, 0664))
				return (print_file_error("minishell: ", temp->token));
		if (temp->type == PIPE)
			do_pipes(cmd_lst, pipes);
		if (cmd_lst->in_fd != -1)
			dup2(cmd_lst->in_fd, STDIN_FILENO);
		if (cmd_lst->out_fd != -1)
			dup2(cmd_lst->out_fd, STDOUT_FILENO);
		temp = temp->next;
	}
	return (0);
}

int	execute_execve(t_command_list *cmd_lst, char **args, t_pipe *pipes)
{
	int	pid;

	if (!pipes)
		return(0);
	pid = fork();
	if (pid == -1)
		ft_putstr_fd("minishell: error forking\n", 2);
	if (pid == 0)
	{
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
			ft_putstr_fd("Command '", 2);
			ft_putstr_fd(cmd_lst->arg[0].token, 2);
			ft_putendl_fd("' not found", 2);
			exit(127);
		}
	}
	return (0);
}

void	revert_fds(t_command_list *cmd_lst)
{
	if (cmd_lst->in_fd != -1)
		close(cmd_lst->in_fd);
	if (cmd_lst->out_fd != -1)
		close(cmd_lst->out_fd);
	dup2(cmd_lst->stdin, STDIN_FILENO);
	close(cmd_lst->stdin);
	dup2(cmd_lst->stdout, STDOUT_FILENO);
	close(cmd_lst->stdout);
}

int	check_cmd(t_command_list *cmd_lst, t_pipe *pipes)
{
	char	**arg_list;
	int		no_of_forks;

	no_of_forks = 0;
	while (cmd_lst)
	{
		cmd_lst->stdin = dup(STDIN_FILENO);
		cmd_lst->stdout = dup(STDOUT_FILENO);
		arg_list = get_arg_list(cmd_lst->arg);
		if (check_fds(cmd_lst, pipes))
		{
			free(arg_list);
			revert_fds(cmd_lst);
		}
		// if (is_builtin(cmd_lst->exec_name))
		//     execute_builtin(cmd_lst);
		else
		{
			execute_execve(cmd_lst, arg_list, pipes);
			free(arg_list);
			revert_fds(cmd_lst);
		}
		no_of_forks++;
		cmd_lst = cmd_lst->next;
		wait(NULL);
	}
	return (0);
}

int	main(void)
{
	t_data data;
	data.pipes.open = 0;
	pipe(data.pipes.fd);
	data.pipes.next = malloc(sizeof(t_pipe));
	data.pipes.next->open = 0;
	data.pipes.next->next = &data.pipes;
	pipe(data.pipes.next->fd);
	t_command_list *cmd_lst = (t_command_list *)malloc(sizeof(t_command_list));
	t_command_list *temp = cmd_lst;
	cmd_lst->exec_path = "/usr/bin/wc";
	cmd_lst->arg = malloc(sizeof(t_arg));
	cmd_lst->next = NULL;
	cmd_lst->in_fd = -1;
	cmd_lst->out_fd = -1;
	t_arg *arg = cmd_lst->arg;
	arg->token = "ls";
	arg->type = STR;
	// arg->next = malloc(sizeof(t_arg));
	// arg = arg->next;
	// arg->token = "-w";
	// arg->type = STR;
	// arg->next = malloc(sizeof(t_arg));
	// arg = arg->next;
	// arg->token = "file1";
	// arg->type = IN;
	arg->next = malloc(sizeof(t_arg));
	arg = arg->next;
	arg->token = "file1";
	arg->type = OUT;
	// arg->next = malloc(sizeof(t_arg));
	// arg = arg->next;
	// arg->token = "file6";
	// arg->type = 2;
	arg->next = NULL;

	cmd_lst->next = (t_command_list *)malloc(sizeof(t_command_list));
	cmd_lst = cmd_lst->next;
	cmd_lst->exec_path = "/usr/bin/echo";
	cmd_lst->arg = malloc(sizeof(t_arg));
	cmd_lst->next = NULL;
	cmd_lst->in_fd = -1;
	cmd_lst->out_fd = -1;
	t_arg *arg2 = cmd_lst->arg;
	arg2->token = "echo";
	arg2->type = STR;
	arg2->next = malloc(sizeof(t_arg));
	arg2 = arg2->next;
	arg2->token = "fileasddd";
	arg2->type = STR;
	arg2->next = malloc(sizeof(t_arg));
	arg2 = arg2->next;
	arg2->token = "file";
	arg2->type = PIPE;
	// arg2->next = malloc(sizeof(t_arg));
	// arg2 = arg2->next;
	// arg2->token = "file4";
	// arg2->type = 2;
	arg2->next = NULL;
	cmd_lst->next = NULL;
	// arg->next = malloc(sizeof(t_arg));
	// arg = arg->next;
	// // arg->token = "file";
	// // arg->type = 1;
	// // arg->next = malloc(sizeof(t_arg));
	// // arg = arg->next;
	// // arg->token = "filerror";
	// // arg->type = 1;
	// arg->next = malloc(sizeof(t_arg));
	// arg = arg->next;
	// arg->token = "file2";
	// arg->type = 2;
	// arg->next = NULL;
	check_cmd(temp, &data.pipes);
	cmd_lst = temp;
	while (cmd_lst)
	{
		t_command_list *temp_c = cmd_lst;
		while (cmd_lst->arg)
		{
			t_arg *temp = cmd_lst->arg;
			cmd_lst->arg = cmd_lst->arg->next;
			free(temp);
		}
		cmd_lst = cmd_lst->next;
		free(temp_c);
	}
}