/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_unclosed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:04:01 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/15 18:10:45 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief returns 1 if the string has unclosed quotes or parenthesis;
 *
 * @param str
 * @return int
 */

#include "includes/minishell.h"

int	print_syntax_error(char c)
{
	ft_putstr_fd("minishell: syntax error: missing token '", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd("'", 2);
	return (2);
}

int	check_unclosed(char *str)
{
	char	c;
	int		i;

	c = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"')
			c = '"';
		else if (str[i] == '\'')
			c = '\'';
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

// int	main(int ac, char **av)
// {
// 	if (ac == 2)
// 		check_unclosed(av[1]);
// }
