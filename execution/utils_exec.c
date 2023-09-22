/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:04:18 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/22 16:42:27 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_arg_list(t_arg *arg)
{
	int		len;
	int		i;
    int j;
	char	**arg_list;

	len = 0;
	i = 0;
	while (arg[i].token != NULL)
	{
		if (arg[i].type == 0)
			len++;
		i++;
	}
	arg_list = (char **)ft_calloc(len + 1, sizeof(char *));
	i = 0;
    j = 0;
	while (arg[i].token != NULL)
	{
		if (arg[i].type == 0)
			arg_list[j++] = ft_strdup(arg[i].token);
		i++;
	}
	return (arg_list);
}

int	open_file(int *fd, char *filename, int flags, int perms)
{
	if (*fd != -1)
	{
		fprintf(stderr, "closed %d\n", *fd);
		close(*fd);
	}
	*fd = open(filename, flags, perms);
	if (*fd == -1)
		return (1);
	fprintf(stderr, "opened \"%s\" on fd %d\n", filename, *fd);
	return (0);
}

void	revert_fds(t_command_list *cmd_lst)
{
	dup2(cmd_lst->stdin, STDIN_FILENO);
	close(cmd_lst->stdin);
	dup2(cmd_lst->stdout, STDOUT_FILENO);
	close(cmd_lst->stdout);
}

int	check_path(char **path, t_command_list *cmd_lst)
{
	int i;
	char *temp;
	char *path_to_test;

	i = 0;
    if (*cmd_lst->arg[0].token == '/')
    {
        cmd_lst->exec_path = ft_strdup(cmd_lst->arg[0].token);
        return (0);
    }
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		path_to_test = ft_strjoin(temp, cmd_lst->arg[0].token);
		free(temp);
		if (access(path_to_test, X_OK | F_OK) == 0)
		{
			cmd_lst->exec_path = path_to_test;
			return (0);
		}
		i++;
	}
	cmd_lst->exec_path = NULL;
	return (0);
}