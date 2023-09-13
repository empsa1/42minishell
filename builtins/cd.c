/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:53:27 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/13 22:49:33 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	change_dir(char *buf, char *str)
{
	if (chdir(buf) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(str, 2);
		return (errno);
	}
	return (0);
}

int	empty_path(t_data *data, char *buf)
{
	int		i;
	t_node	*temp;

	i = -1;
	temp = data->env;
	while (temp->next)
	{
		if (!ft_strncmp(temp->content, "HOME=", 5))
		{
			while (temp->content[5 + ++i])
				buf[i] = temp->content[5 + i];
			while (buf[i])
				buf[i++] = 0;
		}
		temp = temp->next;
	}
	return (0);
}

void	change_pwd_oldpwd(t_node *temp, char *buf, char *oldpwd)
{
	while (temp->next)
	{
		if (!ft_strncmp(temp->content, "OLDPWD=", 7))
		{
			free(temp->content);
			temp->content = ft_strjoin("OLDPWD=", oldpwd);
		}
		if (!ft_strncmp(temp->content, "PWD=", 4))
		{
			free(temp->content);
			temp->content = ft_strjoin("PWD=", buf);
		}
		temp = temp->next;
	}
}

int	cd(t_data *data, char *str)
{
	char	*oldpwd;
	char	buf[PATH_MAX];
    int i;

    i = -1;
	getcwd(buf, PATH_MAX);
    oldpwd = ft_strdup(buf);
    if (!str)
		empty_path(data, buf);
	else if (expand_path(str, buf))
	{
		ft_putstr_fd("minishell: cd: too many arguments: ", 2);
		ft_putendl_fd(str, 2);
		return (-1);
	}
    printf("change to %s\n", buf);
	if (change_dir(buf, str))
		return (errno);
	change_pwd_oldpwd(data->env, buf, oldpwd);
	return (0);
}