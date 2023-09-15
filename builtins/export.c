/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:56:45 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/15 15:48:10 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief	if empty command: print sorted env + sorted exported vars
 *
 * 			if not empty: for each word
 * 				if (key=value) pair
 * 					search env for key, and replace with value;
 * 					if key not found: add key=value pair to exported vars
 * 				else if (key)
 * 					search exported vars for key
 * 					if key not found, add key to exported vars
 *				else if (key=)
					search exported vars for key, replace value with ""
 * 					if key not found, add key to exported vars
 *
 * 				env only prints keys with =, not ordered alphabetically
 * @param temp
 * @param str
 */

void sort_exp(t_node *node)
{
	t_node *cur;
	t_node *next;
	char *temp;

	cur = node;
	next = node->next;
	while (cur && next)
	{
		if (ft_strncmp(cur->content, next->content,
					   ft_strlen(cur->content)) > 0)
		{
			temp = cur->content;
			cur->content = next->content;
			next->content = temp;
			cur = node;
			next = node->next;
		}
		else
		{
			cur = cur->next;
			next = cur->next;
		}
	}
}

t_node *copy_list(t_node *src)
{
	t_node *res;
	t_node *temp;

	res = malloc(sizeof(t_node));
	temp = res;
	while (src)
	{
		temp->content = ft_strdup(src->content);
		if (src->next)
		{
			temp->next = malloc(sizeof(t_node));
			temp = temp->next;
		}
		else
			temp->next = NULL;
		src = src->next;
	}
	return (res);
}

void print_exported(t_node *exp)
{
	t_node *temp;
	int equal_exists;

	if (!exp->content)
		return;
	temp = exp;
	while (temp)
	{
		equal_exists = get_length_to_char(temp->content, '=');
		if (equal_exists && !temp->content[equal_exists + 1])
				printf("declare -x %s\"\"\n", temp->content);
		else
			printf("declare -x %s\n", temp->content);
		temp = temp->next;
	}
}

int replace_in_list(t_node *node, char *str)
{
	t_node *temp;

	temp = node;
	while (temp)
	{
		if (!ft_strncmp(temp->content, str, get_length_to_char(str, '=')))
		{
			free(temp->content);
			temp->content = ft_strdup(str);
			// printf("%s\n", temp->content);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void add_to_list(t_node *node, char *str)
{
	t_node *temp;

	temp = node;
	while (temp->next)
		temp = temp->next;
	temp = malloc(sizeof(t_node));
	temp->content = ft_strdup(str);
	temp->next = NULL;
}

int export(t_data *data, char *str)
{
	t_node *exp;

	exp = data->exported_vars;
	if (!str)
	{
		exp = copy_list(data->env);
		sort_exp(exp);
		print_exported(exp);
		free_nodes(exp);
	}
	else if (!ft_isalnum(*str) && *str != '_')
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("' : not a valid identifier", 2);
		return (-1);
	}
	else if (!get_length_to_char(str, '='))
	{
		if (replace_in_list(data->exported_vars, str))
		{
			printf("replace in exported vars\n");
			return (0);
		}
		printf("adding to list\n");
		add_to_list(data->exported_vars, str);
		return (0);
	}
	printf("check env\n");
	if (!replace_in_list(data->env, str))
	{
		printf("add to exported vars\n");
		add_to_list(data->exported_vars, str);
	}
	return (0);
}
