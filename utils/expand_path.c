/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 08:26:07 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/27 12:11:13 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	check_start(char **str, char *buf)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = PATH_MAX - 1;
// 	if (*(*str + 1) && (!*(*str + 2) || *(*str + 2) == '/'))
// 	{
// 		if (!strncmp(*str, "..", 2))
// 		{
// 			while (buf[j] != '/')
// 				j--;
// 			ft_bzero(&buf[j], PATH_MAX - j);
// 			(*str) += 2;
// 			return (0);
// 		}
// 	}
// 	if (*(*str) == '/' && !*(*str + 1))
// 	{
// 		ft_bzero(&buf[1], PATH_MAX - 1);
// 		return (1);
// 	}
// 	if (*(*str) == '.' && (!*(*str + 1) || *(*str + 1) == '/'))
// 	{
// 		(*str)++;
// 		return (1);
// 	}
// 	else
// 	{
// 		printf("ERROR!\n");
// 		return (1);
// 	}
// 	return (0);
// }

int	expand_path(char *path)
{
	char	buf[PATH_MAX];
	int		j;
	char	*str;

	ft_bzero(buf, PATH_MAX);
	str = path;
	if (!str)
		return (1);
	getcwd(buf, PATH_MAX);
	printf("pwd: %s\n", buf);
    chdir(str);
	getcwd(buf, PATH_MAX);
	printf("pwd: %s\n", buf);
	// if (check_start(&str, buf))
	// 	return (0);
	// j = ft_strlen(buf) - 1;
	// printf("after check_start %s\n", buf);
	// while (*str)
	// {
	// 	while (*str == '/')
	// 	{
	// 		if (!ft_strncmp(str, "/../", 4))
	// 		{
	// 			printf("Here\n");
	// 			while (buf[j] != '/')
	// 				j--;
	// 			ft_bzero(&buf[j], PATH_MAX - j);
	// 			str += 3;
	// 			printf("dis %s\n", str);
	// 		}
	// 		else
	// 			str++;
	// 	}
	// 	buf[++j] = *(str++);
	// 	printf("%s\n", str);
	// }
	// printf("after loop %s\n", buf);
	return (0);
}

int	main(int ac, char **av)
{
	if (!ac)
		return (1);
	expand_path(av[1]);
}