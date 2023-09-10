/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:00:28 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/10 18:00:41 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	expand_path(char *str, char *buf)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buf[i])
		i++;
	if (buf[i] != '/')
		buf[i++] = '/'; //// CLEAN UP!
	while (str[j])
	{
		if (!ft_strncmp(&str[j], "/.", 2) && str[j + 2] != '.')
			j += 3;
		else if (!ft_strncmp(&str[j], "/..", 3) || !ft_strncmp(&str[j], "../",
				3))
		{
			i -= 2;
			while (buf[i] != '/')
				buf[i--] = 0;
			buf[i] = 0;
			j += 3;
		}
		buf[i++] = str[j++];
	}
	buf[i] = '\0';
}