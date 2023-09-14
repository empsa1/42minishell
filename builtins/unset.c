/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:43:40 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/14 09:50:23 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_key_size(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

void	check_env(t_node *cur_node, t_node *prev_node, char *str)
{
	while (cur_node)
	{
		if ((int)ft_strlen(str) == get_key_size(cur_node->content)
			&& !ft_strncmp(cur_node->content, str, ft_strlen(str)))
		{
			free(cur_node->content);
			prev_node->next = cur_node->next;
			free(cur_node);
			return ;
		}
		prev_node = cur_node;
		cur_node = cur_node->next;
	}
}

int	unset(t_data *data, char *str)
{
	t_node	*prev_node;
	t_node	*cur_node;
	int		i;

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
	check_env(cur_node, prev_node, str);
	return (0);
}
