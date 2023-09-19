/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:05:45 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/19 05:26:18 by anda-cun         ###   ########.fr       */
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

int	check_fds(t_command_list *cmd_list)
{
	t_arg	*temp;

	temp = cmd_list->arg;
	while (temp)
	{
		if (temp->type == 1)
		{
			if (cmd_list->in_fd != -1)
				close(cmd_list->in_fd);
			if ((cmd_list->in_fd = open(temp->token, O_RDONLY)) == -1)
				return (print_file_error("minishell: ", temp->token));
		}
		if (temp->type == 2)
		{
			printf("Ooutfd\n");
			if (cmd_list->out_fd != -1)
				close(cmd_list->out_fd);
			if (cmd_list->out_fd = open(temp->token,
					O_CREAT | O_WRONLY | O_TRUNC, 0664) == -1)
				return (print_file_error("minishell: ", temp->token));
			printf("%d\n", cmd_list->out_fd);
		}
		temp = temp->next;
		if (cmd_list->in_fd != -1)
			dup2(cmd_list->in_fd, STDIN_FILENO);
		if (cmd_list->out_fd != -1)
			dup2(cmd_list->out_fd, STDOUT_FILENO);
	}
	return (0);
}

int	execute_execve(t_command_list *cmd_list, char **args)
{
    int pid;
    
	pid = fork();
	if (pid == -1)
		ft_putstr_fd("minishell: error forking\n", 2);
    if (pid != 0)
        close(STDIN_FILENO); //CHECK DIS
	if (pid == 0)
	{
		if (execve(cmd_list->exec_path, args, NULL) == -1)
		{
			if (cmd_list->in_fd != -1)
				close(cmd_list->in_fd);
			if (cmd_list->out_fd != -1)
				close(cmd_list->out_fd);
			dup2(cmd_list->stdin, STDIN_FILENO);
			dup2(cmd_list->stdout, STDOUT_FILENO);
			close(cmd_list->stdin);
			close(cmd_list->stdout);
			ft_putstr_fd("Command '", 2);
			ft_putstr_fd(cmd_list->exec_name, 2);
			ft_putendl_fd("' not found", 2);
			exit(127);
		}
	}
}

int	revert_fds(t_command_list *cmd_list)
{
	if (cmd_list->in_fd != -1)
	{
		printf("closing %d\n", cmd_list->in_fd);
		close(cmd_list->in_fd);
	}
	if (cmd_list->out_fd != -1)
	{
		printf("closing %d\n", cmd_list->out_fd);
		close(cmd_list->out_fd);
	}
	dup2(cmd_list->stdout, STDOUT_FILENO);
	close(cmd_list->stdout);
	dup2(cmd_list->stdin, STDIN_FILENO);
	close(cmd_list->stdin);
}

int	check_cmd(t_command_list *cmd_lst)
{
	char	**arg_list;
	int		stdin;
	int		stdout;
	int		no_of_forks;

	cmd_lst->stdin = dup(STDIN_FILENO);
	cmd_lst->stdout = dup(STDOUT_FILENO);
	no_of_forks = 0;
	while (cmd_lst)
	{
		arg_list = get_arg_list(cmd_lst->arg);
		if (check_fds(cmd_lst))
		{
			free(arg_list);
			revert_fds(cmd_lst);
			return (2);
		}
		// if (is_builtin(cmd_lst->exec_name))
		//     execute_builtin(cmd_list);
		// else
		if (execute_execve(cmd_lst, arg_list))
		{
			free(arg_list);
			revert_fds(cmd_lst);
			return (127);
		}
		free(arg_list);
		revert_fds(cmd_lst);
		no_of_forks++;
		cmd_lst = cmd_lst->next;
	}
	while (no_of_forks--)
		wait(NULL);
}

int	main(void)
{
	t_command_list *cmd_list = (t_command_list *)malloc(sizeof(t_command_list));
	t_command_list *temp = cmd_list;
	cmd_list->exec_name = "ls";
	cmd_list->exec_path = "/usr/bin/ls";
	cmd_list->arg = malloc(sizeof(t_arg));
	cmd_list->next = NULL;
    cmd_list->in_fd = -1;
    cmd_list->out_fd = -1;
	t_arg *arg = cmd_list->arg;
	arg->token = "ls";
	arg->type = 0;
	arg->next = malloc(sizeof(t_arg));
	arg = arg->next;
	arg->token = "-l";
	arg->type = 0;
	arg->next = malloc(sizeof(t_arg));
	arg = arg->next;
	arg->token = "..";
	arg->type = 0;
	arg->next = malloc(sizeof(t_arg));
	arg = arg->next;
	arg->token = "file3";
	arg->type = 2;
	arg->next = NULL;

	cmd_list->next = (t_command_list *)malloc(sizeof(t_command_list));
	cmd_list = cmd_list->next;
	cmd_list->exec_name = "echo";
	cmd_list->exec_path = "/usr/bin/echo";
	cmd_list->arg = malloc(sizeof(t_arg));
	cmd_list->next = NULL;
    cmd_list->in_fd = -1;
    cmd_list->out_fd = -1;
	t_arg *arg2 = cmd_list->arg;
	arg2->token = "echo";
	arg2->type = 0;
	arg2->next = malloc(sizeof(t_arg));
	arg2 = arg2->next;
	arg2->token = "fileasddd";
	arg2->type = 0;
	arg2->next = malloc(sizeof(t_arg));
	arg2 = arg2->next;
	arg2->token = "file";
	arg2->type = 0;
	// arg2->next = malloc(sizeof(t_arg));
	// arg2 = arg2->next;
	// arg2->token = "file3";
	// arg2->type = 1;
	arg2->next = NULL;
	cmd_list->next = NULL;
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
	check_cmd(temp);
	while (cmd_list)
	{
		t_command_list *temp_c = cmd_list;
		while (cmd_list->arg)
		{
			t_arg *temp = cmd_list->arg;
			cmd_list->arg = cmd_list->arg->next;
			free(temp);
		}
		cmd_list = cmd_list->next;
		free(temp_c);
	}
}