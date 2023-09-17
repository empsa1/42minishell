/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:05:45 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/17 23:28:39 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int execute(char **str)
// {
//     int pid;
//     int wstatus;

//     pid = fork();
//     if (pid == -1)
//     {
//         ft_putstr_fd("Error forking\n", 2);
//         return (1);
//     }
//     if (pid == 0)
//     {
//         if (execve(str[0], str, NULL) == -1)
//         {
//             ft_putendl_fd("minishell: command not found: ", 2);
//             ft_putendl_fd(str[0], 2);
//         }
//     }
//     else
//         waitpid(-1, &wstatus, 0);

//     return (0);
// }

char	**get_args(t_arg *arg)
{
	int		len;
	int		i;
	t_arg	*temp;
	char	**args;

	temp = arg;
	len = 0;
	while (temp)
	{
		if (temp->type == 0)
			len++;
		temp = temp->next;
	}
	args = ft_calloc(len + 1, sizeof(char));
	i = 0;
	temp = arg;
	while (temp)
	{
		if (temp->type == 0)
			args[i++] = temp->token;
		temp = temp->next;
	}
	i = 0;
	while (i < len)
		printf("%s\n", args[i++]);
	return (args);
}

int	execute(t_arg *arg, char **args)
{
	t_arg	*temp;
	int		stdin;
	int		stdout;
	int		in_fd;
	int		out_fd;
	int		pid;

	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	in_fd = -1;
	out_fd = -1;
	temp = arg;
	while (temp)
	{
		if (temp->type == 1)
		{
			if (in_fd == -1)
				close(in_fd);
			in_fd = open(temp->token, O_RDONLY);
		}
		if (temp->type == 2)
		{
			if (out_fd == -1)
				close(out_fd);
			out_fd = open(temp->token, O_CREAT | O_WRONLY | O_TRUNC, 0664);
		}
		temp = temp->next;
	}
	if (in_fd != -1)
		dup2(in_fd, STDIN_FILENO);
	if (out_fd != -1)
		dup2(out_fd, STDOUT_FILENO);
	pid = fork();
	if (pid == 0)
	{
		execve("/usr/bin/echo", args, NULL);
	}
	wait(NULL);
	// close(in_fd);
	// close(out_fd);
	// dup2(stdin, STDIN_FILENO);
	// dup2(stdout, STDOUT_FILENO);
	// close(stdout);
	// close(stdin);
	// printf("TESTE\n");
	// dup2(stdin, STDIN_FILENO);
}

int	exec_cmd(t_command_list *cmd_lst)
{
	char	**args;

	while (cmd_lst)
	{
		args = get_args(cmd_lst->arg);
		execute(cmd_lst->arg, args);
		// if (is_builtin(cmd_lst->exec_name))
		//     execute_builtin(cmd_list);
		// else
		//     execute(cmd_list);
		cmd_lst = cmd_lst->next;
	}
}

int	main(void)
{
	t_command_list *cmd_list = malloc(sizeof(t_command_list));
	cmd_list->exec_name = "echo";
	cmd_list->exec_path = "/usr/bin/echo";
	cmd_list->arg = malloc(sizeof(t_arg));
	cmd_list->next = NULL;
	t_arg *arg = cmd_list->arg;
	arg->token = "echo";
	arg->type = 0;
	arg->next = malloc(sizeof(t_arg));
	arg = arg->next;
	arg->token = "-nai";
	arg->type = 0;
	arg->next = malloc(sizeof(t_arg));
    arg = arg->next;
	arg->token = "coiso";
	arg->type = 0;
	arg->next = malloc(sizeof(t_arg));
	arg = arg->next;
	arg->token = "file";
	arg->type = 1;
	arg->next = malloc(sizeof(t_arg));
	arg = arg->next;
	arg->token = "file2";
	arg->type = 2;
	arg->next = NULL;
	exec_cmd(cmd_list);
}