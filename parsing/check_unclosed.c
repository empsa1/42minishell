/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_unclosed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:04:01 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/19 05:49:37 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief returns 2 if the string has unclosed quotes or parenthesis;
 *
 * @param str
 * @return int
 */

#include "../includes/minishell.h"

int	check_unclosed(char *str)
{
	char	c;
	int		i;

	c = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == ')')
			return (print_syntax_error(')'));
		if (str[i] == '"' || str[i] == '\'')
			c = str[i];
		else if (str[i] == '(')
			c = ')';
		if (c)
		{
			while (str[++i])
				if (str[i] == c)
					break ;
			if (str[i] != c)
				return (print_syntax_error(c));
			c = 0;
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	if (ac > 1)
		return (check_unclosed(av[1]));
}
