/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:00:28 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/12 13:26:35 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	check_root(char *str, char *buf)
{
	if (!ft_strncmp(str, "/\0", 2))
	{
		ft_bzero(&buf[1], PATH_MAX - 1);
		return (1);
	}
	return (0);
}

int	expand_path(char *str, char *buf)
{
	int	i;
	int	j;

	j = 0;
	if (check_root(str, buf))
		return (0);
	i = ft_strlen(buf);
	buf[i] = '/';
	while (str[j] && str[j] != ' ')
	{
		if (!ft_strncmp(&str[j], "./", 2))
			j += 2;
		else if (!ft_strncmp(&str[j], "../", 3))
		{
			while (buf[i - 1] != '/')
				buf[i--] = 0;
			buf[i] = 0;
			j += 3;
		}
		if (str[j])
			buf[++i] = str[j++];
	}
	buf[++i] = '\0';
	return (0);
}
