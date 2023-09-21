/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_unclosed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eportela <eportela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:04:01 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/21 15:27:00 by eportela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief returns 2 if the string has unclosed quotes or parenthesis;
 *
 * @param str
 * @return int
 */

#include "minishell.h"

int	check_parenthesis(char *str)
{
	char	*tester;
	int		i;
	int		j;

	i = 0;
	tester = ft_strdup(str);
	while (tester[i] == ' ')
		i++;
	if (*tester == ')')
		return (print_syntax_error(')'));
	while (tester[i])
	{
		if (tester[i++] == '(')
		{
			j = i;
			while (tester[j++])
			{
				if (tester[j] == ')')
				{
					tester[j] = 2;
					break;
				}
			}
		}
	}
	printf("%s\n", tester);
	free(tester);
	return (0);
}

// int	check_parenthesis(char *str)
// {
// 	int		i;
// 	int		j;
// 	char	c;

// 	i = -1;
// 	j = 0;
// 	c = 0;
// 	while (str[++i])
// 	{
// 		printf("checking %c\n", str[i]);
// 		if (str[i] == ')')
// 		{
// 			printf("Here\n");
// 			return (print_syntax_error(')'));
// 		}
// 		if (str[i] == '(')
// 		{
// 			printf("found (\n");
// 			if (j == 0)
// 				j = i;
// 			while (str[j++])
// 			{
// 				if (str[j] == ')')
// 				{
// 					printf("found )\n");
// 					i++;
// 					break ;
// 				}
// 			}
// 			if (str[j] != ')')
// 				return (print_syntax_error(str[j]));
// 		}
// 	}
// 	return (0);
// }

int	check_unclosed(char *str)
{
	char	c;
	int		i;

	c = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
			c = str[i];
		if (c)
		{
			while (str[++i])
				if (str[i] == c)
				{
					printf("%c not found\n", c);
					break ;
				}
			if (str[i] != c)
				return (print_syntax_error(c));
			c = 0;
		}
		return (check_parenthesis(str));
	}
	return (0);
}

// int	main(int ac, char **av)
// {
// 	if (ac > 1)
// 		return (check_unclosed(av[1]));
// }
