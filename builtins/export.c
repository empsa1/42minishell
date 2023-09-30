/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:59:30 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/28 11:33:19 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_dupes(t_pair *env, char *str)
{
	t_pair	*temp;
	int		str_size;

	temp = env;
	str_size = len_to_char(str, '=');
	while (temp)
	{
		if (!ft_strncmp(str, temp->key, str_size) && (!temp->key[str_size]
				|| temp->key[str_size] == '='))
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
		temp->key = ft_substr(str, 0, len_to_char(str, '=') + 1);
		temp->value = ft_strdup(ft_strchr(str, '=') + 1);
	}
	temp->next = NULL;
}

int	replace_var(t_pair *env, char *str)
{
	t_pair	*temp;
	char *temp_str;

	temp = env;
	while (temp)
	{
		if (!ft_strncmp(str, temp->key, len_to_char(str, '=')))
		{
			if (!ft_strchr(temp->key, '='))
			{
				temp_str = temp->key;
				temp->key = ft_strjoin(temp_str, "=");
				free(temp_str);
			}
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

int	print_sorted_all(t_pair *env, t_pair *exported_vars)
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
	return (0);
}

/*
If string doesn't start with an alphanum char or with a '_', return (error); OK

If string doesn't have a '='
	if string is not in env list && string is not in exported list
		add to exported list

If string has a '=':
	if string is in env list
		replace value
	else if string is not in env list
		if string is in exported list
			replace string
		else
			add to exported vars
 */

int	export(t_data *data, char **str)
{
	t_pair	*env;
	t_pair	*exported_vars;
	int		i;

	env = data->env;
	exported_vars = data->exported_vars;
	i = -1;
	if (!*str)
		return (print_sorted_all(env, exported_vars));
	while (str[++i])
	{
		if (!ft_isalnum(*str[i]) && *str[i] != '_')
		{
			ft_putstr_fd("minishell: export: `", 1);
			ft_putstr_fd(str[i], 1);
			ft_putendl_fd("': not a valid identifier", 1);
		}
		if (!ft_strchr(str[i], '='))
		{
			if ((!check_dupes(env, str[i]) && !exported_vars->key)
				|| (exported_vars->key && !check_dupes(exported_vars, str[i])))
				add_to_list(str[i], exported_vars);
		}
		else
		{
			if (check_dupes(env, str[i]))
				replace_var(env, str[i]);
			else if (exported_vars->key && check_dupes(exported_vars, str[i]))
				replace_var(exported_vars, str[i]);
			else
				add_to_list(str[i], exported_vars);
		}
	}
	return (0);
}
