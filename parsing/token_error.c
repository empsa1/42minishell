/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 11:57:59 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/30 15:45:40 by anda-cun         ###   ########.fr       */
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
			printf("Here1\n");
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
	int	i;
	int j;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '|')
	{
		data->exit_status = 2;
		return (print_syntax_error(str[i]));
	}
	while (str[i] != 0)
	{
		j = 0;
		if (!ft_strncmp(&str[i], "<<", 2) || !ft_strncmp(&str[i], ">>", 2))
			j += 2;
		else if (ft_strchr("<>|", str[i]))
			j += 1;
		if (j && check_unexpected_token(data, &str[i + j]))
			return (1);
		i++;
	}
	return (check_end_of_command(data, str));
}
