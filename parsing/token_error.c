/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 11:57:59 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/26 07:39:17 by anda-cun         ###   ########.fr       */
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

int	check_end_of_command(t_data *data, char *str)
{
	int	i;

	i = ft_strlen(str);
	i--;
	while (str[i])
	{
		while (str[i] == ' ')
			i--;
		if (!str[i])
			break ;
		if (ft_strchr("<>|", str[i]))
		{
			data->exit_status = 2;
			return (print_syntax_error(str[i + 1]));
		}
		break ;
	}
	return (0);
}

int	check_unexpected_token(t_data *data, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] && ft_strchr("<>|", str[i]))
	{
		data->exit_status = 2;
		return (print_syntax_error(str[i]));
	}
	return (0);
}

int	token_error(t_data *data, char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] != 0)
	{
		if (!ft_strncmp(&str[i], "<<", 2) || !ft_strncmp(&str[i], ">>", 2))
		{
			if (check_unexpected_token(data, &str[i + 2]))
			{
				data->exit_status = 2;
				return (1);
			}
		}
		else if (ft_strchr("<>|", str[i]))
		{
			if (check_unexpected_token(data, &str[i + 1]))
			{
				data->exit_status = 2;
				return (1);
			}
		}
		i++;
	}
	return (check_end_of_command(data, str));
}