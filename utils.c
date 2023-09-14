/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:56:07 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/14 17:09:19 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int get_length_to_char(char *str, char c)
{
	int len;

	len = -1;
	while (str[++len])
		if(str[len] == c)
			return(len);
	return (0);
}