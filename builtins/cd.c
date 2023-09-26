/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:53:27 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/26 16:56:11 by anda-cun         ###   ########.fr       */
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
	t_pair	*temp;

	i = -1;
	temp = data->env;
	while (temp->next)
	{
		if (!ft_strncmp(temp->key, "HOME=", 5))
		{
			while (temp->key[5 + ++i])
				buf[i] = temp->key[5 + i];
			while (buf[i])
				buf[i++] = 0;
		}
		temp = temp->next;
	}
	return (0);
}

void	change_pwd_oldpwd(t_pair *temp, char *buf, char *oldpwd)
{
	while (temp->next)
	{
		if (!ft_strncmp(temp->key, "OLDPWD=", 7))
		{
			free(temp->key);
			temp->key = ft_strjoin("OLDPWD=", oldpwd);
		}
		if (!ft_strncmp(temp->key, "PWD=", 4))
		{
			free(temp->key);
			temp->key = ft_strjoin("PWD=", buf);
		}
		temp = temp->next;
	}
}

int	cd(t_data *data, char **str)
{
	char	*oldpwd;
	char	buf[PATH_MAX];

	getcwd(buf, PATH_MAX);
    oldpwd = ft_strdup(buf);
    if (!str[1])
		empty_path(data, buf);
	else if (expand_path(str[1], buf))
	{
		ft_putstr_fd("minishell: cd: too many arguments: ", 2);
		ft_putendl_fd(str[1], 2);
		return (-1);
	}
    printf("change to %s\n", buf);
	if (change_dir(buf, str[1]))
		return (errno);
	change_pwd_oldpwd(data->env, buf, oldpwd);
	return (0);
}