/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:04:18 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/29 06:06:03 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_cmd(char **arg_list, t_command_list *cmd_lst, int *heredoc)
{
	if (*heredoc)
	{
		unlink("heredoc_163465");
		*heredoc = 0;
	}
	if (arg_list)
		free(arg_list);
	free_args(cmd_lst->arg);
	free(cmd_lst->exec_path);
}

char	**get_arg_list(t_arg *arg)
{
	int		len;
	int		i;
	int		j;
	char	**arg_list;

	len = 0;
	i = 0;
	while (arg[i].token != NULL)
	{
		if (arg[i].type == 0)
			len++;
		i++;
	}
	if (len)
		arg_list = (char **)ft_calloc(len + 1, sizeof(char *));
	else
		return (NULL);
	i = 0;
	j = 0;
	while (arg[i].token != NULL)
	{
		if (arg[i].type == 0)
			arg_list[j++] = arg[i].token;
		i++;
	}
	return (arg_list);
}

int	open_file(int *fd, char *filename, int flags, int perms)
{
	if (*fd != -1)
		close(*fd);
	*fd = open(filename, flags, perms);
	if (*fd == -1)
		return (1);
	return (0);
}

void	revert_fds(t_command_list *cmd_lst)
{
	fprintf(stderr, "closed %d\n", cmd_lst->stdin);
	dup2(cmd_lst->stdin, STDIN_FILENO);
	close(cmd_lst->stdin);
	fprintf(stderr, "closed %d\n", cmd_lst->stdout);
	dup2(cmd_lst->stdout, STDOUT_FILENO);
	close(cmd_lst->stdout);
}

char **get_path(t_data *data)
{
	while (data->env)
	{
		if (!ft_strncmp(data->env->key, "PATH=", 5))
			return (ft_split(data->env->value, ':'));
		data->env = data->env->next;
	}
	return (NULL);
}

int	check_path(t_data *data, t_command_list *cmd_lst, char *str)
{
	int i;
	char *temp;
	char *path_to_test;

	(void) data;
	data->path = get_path(data);
	char **path = data->path;
	if (!*path)
	{
		fprintf(stderr, "PATH not found\n");
		return(0);
	}
	path_to_test = NULL;
	i = 0;
	if (*str == '/')
	{
		cmd_lst->exec_path = ft_strdup(str);
		return (0);
	}
	while (path[i])
	{
		if (path[i][ft_strlen(path[i]) - 1] != '/')
			temp = ft_strjoin(path[i], "/");
		else
			temp = ft_strdup(path[i]);
		path_to_test = ft_strjoin(temp, str);
		free(temp);
		if (access(path_to_test, X_OK | F_OK) == 0)
		{
			cmd_lst->exec_path = path_to_test;
			return (0);
		}
		else if (path[i + 1])
			free(path_to_test);
		i++;
	}
	cmd_lst->exec_path = path_to_test;
	return (0);
}
