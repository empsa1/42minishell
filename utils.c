/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:56:07 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/16 19:57:35 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int get_length_to_char(char *str, char c)
{
	int len;

	if (!str)
		return(0);
	len = -1;
	while (str[++len])
		if(str[len] == c)
			return(len);
	return (0);
}

void free_nodes(t_node *node)
{
	t_node *temp;
	while (node)
	{
		free(node->content);
		temp = node->next;
		free(node);
		node = temp;
	}
	free(node);
}

void free_pairs(t_pair *pair)
{
	t_pair *temp;
	while (pair)
	{
		free(pair->key);
		free(pair->value);
		temp = pair->next;
		free(pair);
		pair = temp;
	}
	free(pair);
}

void print_nodes(t_node *node)
{
	t_node *temp;
	
	temp = node;
	while (temp)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
}

void print_pairs(t_pair *pair)
{
	t_pair *temp;
	
	temp = pair;
	while (temp)
	{
		printf("%s%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}