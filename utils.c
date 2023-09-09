/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:14:12 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/09 18:12:36 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void check_line(char *line)
{
	int i;
	int j;
	char *tokens;

	
	i = 0;
	j = 0;
	tokens = "|('\"<>\"";
	while (line[i])
	{
		if (ft_strchr(tokens, line[i]))
		{
			while (line[j])
			{
				if (ft_strchr(tokens, line[j]))
					printf("yadda %s\n", &line[j + 1]);
			j++;
			}
			i = j;
		}
		i++;
	}
}

int	print_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (1);
}