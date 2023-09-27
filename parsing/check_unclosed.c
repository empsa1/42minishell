/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_unclosed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:04:01 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/27 15:15:10 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief returns 2 if the string has unclosed quotes or parenthesis;
 *
 * @param str
 * @return int
 */

#include "minishell.h"

// int	check_parenthesis(char *str)
// {
// 	char	*tester;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	tester = ft_strdup(str);
// 	while (tester[i] == ' ')
// 		i++;
// 	if (*tester == ')')
// 		return (print_syntax_error(')'));
// 	while (tester[i])
// 	{
// 		if (tester[i++] == '(')
// 		{
// 			j = i;
// 			while (tester[j++])
// 			{
// 				if (tester[j] == ')')
// 				{
// 					tester[j] = 2;
// 					break;
// 				}
// 			}
// 		}
// 	}
// 	printf("%s\n", tester);
// 	free(tester);
// 	return (0);
// }

int	check_unclosed(t_data *data, char *str)
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
					break ;
			if (str[i] != c)
			{
				data->exit_status = 2;	
				return (print_syntax_error(c));
			}
			c = 0;
		}
	}
	return (0);
}

// int	main(int ac, char **av)
// {
// 	if (ac > 1)
// 		return (check_unclosed(av[1]));
// }
