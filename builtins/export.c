/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:59:30 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/26 17:11:53 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_dupes(t_pair *env, char *str)
{
	t_pair	*temp;

	temp = env;
	while (temp)
	{
		if (!ft_strncmp(str, temp->key, ft_strlen(str)))
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	add_to_list(char *str, t_pair *exported_vars)
{
	t_pair	*temp;

	temp = exported_vars;
	if (temp->key)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = malloc(sizeof(t_pair));
		temp = temp->next;
	}
	if (!ft_strchr(str, '='))
	{
		temp->key = ft_strdup(str);
		temp->value = NULL;
	}
	else
	{
		temp->key = ft_substr(str, 0, get_length_to_char(str, '=') + 1);
		temp->value = ft_strdup(ft_strchr(str, '=') + 1);
	}
	temp->next = NULL;
}

int	replace_var(t_pair *env, char *str)
{
	t_pair	*temp;

	temp = env;
	while (temp)
	{
		if (!ft_strncmp(str, temp->key, get_length_to_char(str, '=')))
		{
			free(temp->value);
			temp->value = ft_strdup(ft_strchr(str, '=') + 1);
		}
		temp = temp->next;
	}
	return (0);
}

t_pair	*copy_list_all(t_pair *env, t_pair *exported_vars)
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
		if (temp_env || exported_vars)
		{
			temp_export->next = malloc(sizeof(t_pair));
			temp_export = temp_export->next;
		}
		else
			temp_export->next = NULL;
	}
	temp_env = exported_vars;
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

void	print_sorted_all(t_pair *env, t_pair *exported_vars)
{
	t_pair	*export;
	t_pair	*temp_export;

	export = copy_list_all(env, exported_vars);
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

int	export(t_data *data, char **str)
{
	t_pair *env;
	t_pair *exported_vars;
	int	i;

	env = data->env;
	exported_vars = data->exported_vars;
	i = -1;
	if (!str)
	{
		print_sorted_all(env, exported_vars);
		return (0);
	}
	while (str[++i])
	{
		if (!ft_isalnum(*str[i]) && *str[i] != '_')
			return(print_syntax_error(*str[i + 1]));
		if (!ft_strchr(str[i], '='))
		{
			if (!check_dupes(env, str[i]))
				add_to_list(str[i], exported_vars);
		}
		else
		{
			if (!check_dupes(env, str[i]))
				replace_var(env, str[i]);
			else
				add_to_list(str[i], exported_vars);
		}
	}
	return(0);
}
