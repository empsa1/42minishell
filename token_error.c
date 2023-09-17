/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 11:57:59 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/17 11:40:48 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	check_unexpected_token(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] && ft_strchr("<>|", str[i]))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putchar_fd(str[i], 2);
		ft_putendl_fd("'", 2);
		return (1);
	}
	return (0);
}

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
}

// int	main(int ac, char **av)
// {
// 	if (ac > 0)
// 		token_error(av[1]);
// }
