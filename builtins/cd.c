/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:53:27 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/27 15:15:10 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	change_dir(char *str)
{
	if (chdir(str) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	return (0);
}

void	change_pwd_oldpwd(t_pair *temp, char *buf, char *oldpwd)
{
	while (temp->next)
	{
		if (!ft_strncmp(temp->key, "OLDPWD=", 7))
		{
			free(temp->value);
			temp->value = oldpwd;
		}
		if (!ft_strncmp(temp->key, "PWD=", 4))
		{
			free(temp->value);
			temp->value = ft_strdup(buf);
		}
		temp = temp->next;
	}
}

int	cd(t_data *data, char **str)
{
	char	*oldpwd;
	char	*new_path;
	char	pwd[PATH_MAX];

	new_path = str[0];
	(void)data;
	getcwd(pwd, PATH_MAX);
	oldpwd = ft_strdup(pwd);
	if (str[0] && str[1])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		data->exit_status  = 1;
		free(oldpwd);
		return (0);
	}
	if (!new_path)
		new_path = "/";
	data->exit_status = change_dir(new_path);
	getcwd(pwd, PATH_MAX);
	if (!data->exit_status)
		change_pwd_oldpwd(data->env, pwd, oldpwd);
	else
		free(oldpwd);
	return (0);
}
