/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_unclosed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:04:01 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/19 13:22:22 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief returns 2 if the string has unclosed quotes or parenthesis;
 *
 * @param str
 * @return int
 */

#include "../includes/minishell.h"

int	check_parenthesis(char *str)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	j = 0;
	c = 0;
	while (str[++i])
	{
		printf("%c\n", str[i]);
		if (str[i] == ')')
		{
			printf("Here\n");
			return (print_syntax_error(')'));
		}
		if (str[i] == '(')
		{
			printf("found (\n");
			if (j == 0)
				j = i;
			while (str[j++])
			{
				if (str[j] == ')')
				{
					printf("found )\n");
					break ;
				}
				if (!str[j])
					printf("ERROR\n");
			}
		}
	}
	return (0);
}

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

int	main(int ac, char **av)
{
	if (ac > 1)
		return (check_unclosed(av[1]));
}
