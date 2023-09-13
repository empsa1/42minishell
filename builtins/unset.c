/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:43:40 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/13 16:08:09 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int unset(t_data *data, char *str)
{
	t_env *prev_node;
	t_env *cur_node;
	int i;

	prev_node = NULL;
	cur_node = data->env;
	i = -1;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (!ft_isalnum(str[i]))
		{
			if (str[i] != '_')
			{
				ft_putstr_fd("unset: ", 2);
				ft_putstr_fd(str, 2);
				ft_putendl_fd(": invalid parameter name", 2);
				return (1);
			}
		}
	}
	while (cur_node)
	{
		if (!ft_strncmp(cur_node->content, str, ft_strlen(str)))
		{
			free(cur_node->content);
			prev_node->next = cur_node->next;
			free(cur_node);
			break;
		}
		prev_node = cur_node;
		cur_node = cur_node->next;
	}
	return (0);
}
