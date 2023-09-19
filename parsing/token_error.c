/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 11:57:59 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/19 06:09:50 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**

	* @brief Returns 2 if there are two special tokens without any strings in 
	between, or a special token at end of command;
 *
 * @param str
 * @return int
 */

int	check_end_of_command(char *str)
{
	int	i;

	i = ft_strlen(str);
	while (str[--i])
	{
		if (str[i] == ' ')
			i--;
		if (!str[i])
			break ;
		if (ft_strchr("<>|", str[i]))
			return (print_syntax_error(str[i + 1]));
		else
			return (0);
	}
}

int	check_unexpected_token(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] && ft_strchr("<>|", str[i]))
		return (print_syntax_error(str[i]));
	return (0);
}

/**
 * @brief TESTE asdasdasd
 * 
 * @param str 
 * @return int 
 */

int	token_error(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_strncmp(&str[i], "<<", 2) || !ft_strncmp(&str[i], ">>", 2))
		{
			i += 2;
			if (check_unexpected_token(&str[i]))
				return (1);
		}
		else if (ft_strchr("<>|", str[i]))
		{
			if (check_unexpected_token(&str[++i]))
				return (1);
		}
	}
	check_end_of_command(str);
}

int	main(int ac, char **av)
{
	if (ac > 1)
		return (token_error(av[1]));
}
