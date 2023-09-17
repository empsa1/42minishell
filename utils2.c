/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 00:00:23 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/17 22:15:33 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_pair	*copy_list(t_pair *env)
{
	t_pair	*temp_env;
	t_pair	*export;
	t_pair	*temp_export;

	export = malloc(sizeof(t_pair));
	temp_export = export;
	temp_env = env;
	while (temp_env)
	{
		temp_export->key = ft_strdup(temp_env->key);
		temp_export->value = ft_strdup(temp_env->value);
		temp_env = temp_env->next;
		if (temp_env)
		{
			temp_export->next = malloc(sizeof(t_pair));
			temp_export = temp_export->next;
		}
		else
			temp_export->next = NULL;
	}
	return (export);
}

void	print_sorted(t_pair *env)
{
	t_pair	*temp_env;
	t_pair	*export;
	t_pair	*temp_export;

	temp_env = env;
	export = copy_list(env);
	sort_list(export);
	temp_export = export;
	while (temp_export)
	{
		if (ft_strchr(temp_export->key, '=') && !*temp_export->value)
			printf("declare -x %s\"\"\n", temp_export->key);
		else
			printf("declare -x %s%s\n", temp_export->key, temp_export->value);
		temp_export = temp_export->next;
	}
	free_pairs(export);
}

void	sort_list(t_pair *export)
{
	t_pair	*cur;
	t_pair	*next;
	char	*temp;

	cur = export;
	next = export->next;
	while (cur && next)
	{
		if (ft_strncmp(cur->key, next->key, ft_strlen(cur->key)) > 0)
		{
			temp = cur->key;
			cur->key = next->key;
			next->key = temp;
			temp = cur->value;
			cur->value = next->value;
			next->value = temp;
			cur = export;
			next = export->next;
		}
		else
		{
			cur = cur->next;
			next = cur->next;
		}
	}
}
