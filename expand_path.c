/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:00:28 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/13 15:35:16 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int check_root(char *str, char *buf)
{
	if (!ft_strncmp(str, "/\0", 2))
	{
		ft_bzero(&buf[1], PATH_MAX - 1);
		printf("pqp %s\n", buf);
		return (0);
	}
	return (1);
}

int expand_path2(char *buf, char *str, int *i, int *j)
{
	while (str[*j] && str[*j] != ' ')
	{
		if (!ft_strncmp(&str[*j], "./", 2))
			*j += 2;
		else if (!ft_strncmp(&str[*j], "../", 3))
		{
			if (buf[(*i) - 1])
				buf[(*i)--] = 0;
			while (buf[*i - 1] && buf[*i] != '/')
				buf[(*i)--] = 0;
			*j += 3;
		}
		if (buf[*i] && buf[*i] == '/')
			(*i)++;
		if (str[*j])
			buf[(*i)++] = str[(*j)++];
		(*j)++;
	}
	if (str[*j] && str[*j] == ' ')
		return(-1);
	buf[(*i)] = '\0';
	printf("pathgggg: %s\n", buf);
	return (0);
}

int expand_path(char *str, char *buf)
{
	printf("%s\n", buf);
	int i;
	int j;

	j = 0;
	if (check_root(str, buf))
		return (0);
	i = ft_strlen(buf);
	printf("%c\n", buf[i]);
	if (buf[i] && buf[i - 1] && buf[i - 1] != '/')
		buf[i] = '/';
	if (*str == '.' && !str[1])
		return (0);
	if (!ft_strncmp(str, "..\0", 3))
	{
		if (buf[i - 1])
			buf[i--] = 0;
		while (buf[i - 1] && buf[i] != '/')
			buf[i--] = 0;
		return (0);
	}
	printf("pqp %s\n", buf);
	return (0);
	// return(expand_path2(buf, str, &i, &j));
}
