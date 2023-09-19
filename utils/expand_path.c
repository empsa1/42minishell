/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:00:28 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/19 06:32:21 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_root(char *str, char *buf)
{
	if (!ft_strncmp(str, "/\0", 2))
	{
		ft_bzero(&buf[1], PATH_MAX - 1);
		printf("pqp %s\n", buf);
		return (0);
	}
	return (1);
}

// int	expand_path2(char *buf, char *str)
// {
// 	while (str[*j] && str[*j] != ' ')
// 	{
// 		if (!ft_strncmp(&str[*j], "./", 2))
// 			*j += 2;
// 		else if (!ft_strncmp(&str[*j], "../", 3))
// 		{
// 			if (buf[(*i) - 1])
// 				buf[(*i)--] = 0;
// 			while (buf[*i - 1] && buf[*i] != '/')
// 				buf[(*i)--] = 0;
// 			*j += 3;
// 		}
// 		if (buf[*i] && buf[*i] == '/')
// 			(*i)++;
// 		if (str[*j])
// 			buf[(*i)++] = str[(*j)++];
// 		(*j)++;
// 	}
// 	if (str[*j] && str[*j] == ' ')
// 		return (-1);
// 	buf[(*i)] = '\0';
// 	printf("pathgggg: %s\n", buf);
// 	return (0);
// }

int expand_path2(char *buf, char *str)
{
	int	i;
	int	j;

	i = ft_strlen(buf);
	j = 0;
	while (str[j] && str[j] != ' ')
	{
		if (!ft_strncmp(&str[j], "./", 2))
			j += 2;
		if (!ft_strncmp(&str[j], "../", 3))
		{
			if (buf[i - 1])
				buf[i--] = 0;
			while (buf[i - 1] && buf[i] != '/')
				buf[i--] = 0;
			j -= 3;
		}
		j++;
	}
	buf[i] = 0;
	return (0);
}

int	expand_path(char *str, char *buf)
{
	int	i;

	if (!check_root(str, buf))
		return (0);
	i = ft_strlen(buf);
	if (buf[i] && buf[i - 1] && buf[i - 1] != '/')
		buf[i] = '/';
	if (!ft_strncmp(str, ".\0", 2))
		return (0);
	if (!ft_strncmp(str, "..\0", 3))
	{
		if (buf[i - 1])
			buf[i--] = 0;
		while (buf[i - 1] && buf[i] != '/')
			buf[i--] = 0;
		return (0);
	}
	return (expand_path2(buf, str));
}

int	main(void)
{
	char buf[PATH_MAX];
	char *path = "../";

	getcwd(buf, PATH_MAX);
	printf("original %s\n", buf);
	printf("path: %s\n", path);
	expand_path(path, buf);
	printf("result: %s\n", buf);
}