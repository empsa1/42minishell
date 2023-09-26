/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:05:45 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/26 13:28:43 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	do_pipes(t_command_list *cmd_lst, t_pipe *pipes)
{
	if (cmd_lst->next)
	{
		pipe(pipes->fd);
		pipes->open = 1;
		if (cmd_lst->out_fd == -1)
			cmd_lst->out_fd = pipes->fd[1];
	}
	if (pipes->next->open == 1)
		cmd_lst->in_fd = pipes->next->fd[0];
	return (0);
}

int	assign_fds(int in_fd, int out_fd)
{
	if (in_fd != -1)
	{
		fprintf(stderr, "duping STDIN to %d\n", in_fd);
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != -1)
	{
		fprintf(stderr, "duping STDOUT to %d\n", out_fd);
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	return (0);
}

int	check_fds(t_data *data, t_command_list *cmd_lst, t_pipe *pipes)
{
	int	i;

	i = 0;
	if ((cmd_lst->next || pipes->next->open))
	{
		do_pipes(cmd_lst, pipes);
		fprintf(stderr, "doing pipe\n");
	}
	while (cmd_lst->arg[i].token != NULL)
	{
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
	assign_fds(cmd_lst->in_fd, cmd_lst->out_fd);
	return (0);
}

void	add_pid(t_data *data, int pid)
{
	t_pid	*temp;

	temp = malloc(sizeof(t_pid));
	temp->value = pid;
	temp->next = data->pid;
	data->pid = temp;
	fprintf(stderr, "data->pid value: %d\n", data->pid->value);
}

int	execute_execve(t_data *data, t_command_list *cmd_lst, char **args)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("minishell: error forking\n", 2);
		return (-1);
	}
	if (pid == 0)
	{
		if (execve(cmd_lst->exec_path, args, NULL) == -1)
		{
			if (data->pipes.open)
				close(data->pipes.fd[0]);
			revert_fds(cmd_lst);
			ft_putstr_fd(cmd_lst->arg->token, 2);
			ft_putendl_fd(": command not found", 2);
			exit(127);
		}
	}
	add_pid(data, pid);
	return (0);
}

void	free_pid(t_data *data)
{
	t_pid	*temp;

	while (data->pid->value != 0)
	{
		temp = data->pid;
		data->pid = data->pid->next;
		free(temp);
	}
	data->pid->value = 0;
}

int	check_cmd(t_data *data, t_command_list *cmd_lst, t_pipe *pipes)
{
	char	**arg_list;
	int		no_of_forks;
	int		status;
	t_pid	*pid;

	no_of_forks = 0;
	data->pipes.open = 0;
	data->pipes.next->open = 0;
	data->exit_status = 0;
	while (cmd_lst)
	{
		init_cmd_lst(cmd_lst);
		arg_list = get_arg_list(cmd_lst->arg);
		if (arg_list)
			check_path(data->path, cmd_lst, *arg_list);
		if (check_fds(data, cmd_lst, pipes))
		{
			free_cmd(arg_list, cmd_lst, &data->heredoc);
			revert_fds(cmd_lst);
			data->exit_status = errno;
		}
		else
		{
			fprintf(stderr, "******Executing command: %s******\n", *arg_list);
			// if (is_builtin(cmd_lst->exec_name))
			//     data->exit_status = execute_builtin(cmd_lst);
			// else
			if (!execute_execve(data, cmd_lst, arg_list))
				no_of_forks++;
			pipes = pipes->next;
			free_cmd(arg_list, cmd_lst, &data->heredoc);
			revert_fds(cmd_lst);
		}
		cmd_lst = cmd_lst->next;
	}
	pid = data->pid;
	while (pid->value != 0)
	{
		waitpid(pid->value, &status, 0);
		if (pid->value == data->pid->value)
			data->exit_status = WEXITSTATUS(status);
		pid = pid->next;
	}
	free_pid(data);
	return (data->exit_status);
}
