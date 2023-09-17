/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:43:40 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/17 22:20:48 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t len_to_char(char *str, char c)
{
	int len;

	len = 0;
	if (!str)
		return(0);
	while (str[len])
	{
		if (str[len] == c)
			return(len);
		len++;
	}
	return(len);
}

int	remove_from_list(char *str, t_pair *pair)
{
	t_pair	*prev;
	t_pair *cur;

	cur = pair;
	prev = NULL;
	while (cur)
	{
		if (ft_strlen(str) == len_to_char(cur->key, '=') && !ft_strncmp(str, cur->key, ft_strlen(str)))
		{
			printf("removing %s\n", str);
			if (!prev)
				pair = pair->next;
			else
				prev->next = cur->next;
				printf("should free %s\n", cur->key);
			free(cur->key);
			free(cur->value);
			free(cur);
			return (1);
		}
		prev = cur;
		cur = cur->next;
	}
	return(0);
}

int	unset(t_data *data, char **str)
{
	t_pair	*prev_node;
	t_pair	*cur_node;
	int		i;

	prev_node = NULL;
	cur_node = data->env;
	i = -1;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (!ft_isalnum(*str[i]) && *str[i] != '_' || ft_strchr(str[i], '='))
		{
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd(str[i], 2);
			ft_putendl_fd(": invalid parameter name", 2);
		}
		if (!remove_from_list(str[i], data->exported_vars))
			if (data->exported_vars->key)
				remove_from_list(str[i], data->exported_vars);
	}
	return (0);
}
