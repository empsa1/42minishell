/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:56:45 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/13 23:35:55 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export(t_data *data, char *str)
{
	t_node	*temp;
	t_node	*temp_exp;
	int		i;

	i = -1;
	if (!str)
	{
		env(data, NULL);
		temp_exp = data->exp;
		printf("%p\n", temp_exp);
		if (!temp_exp)
			return (0);
		while (temp_exp)
		{
			printf("%s\n", temp_exp->content);
			temp_exp = temp_exp->next;
		}
	}
	while (str[++i] && str[i] != ' ')
	{
		if (str[i] == '=' && str[i + 1] && str[i + 1] != ' ')
			break ;
	}
	if (str[i] != '=')
	{
		printf("Here\n");
		if (!temp_exp)
			temp_exp = malloc(sizeof(t_node));
		printf("%p\n", temp_exp);
		// else
		// {
		// 	temp_exp->next = malloc(sizeof(t_node));
		// 	temp_exp = temp_exp->next;
		// }
		i = 0;
		while (str[i] != ' ')
			i++;
		temp_exp->content = ft_substr(str, 0, i);
		temp_exp->next = NULL;
		return (0);
	}
	temp = data->env;
	while (temp)
	{
		if (!ft_strncmp(temp->content, str, i + 1))
		{
			free(temp->content);
			temp->content = ft_strdup(str);
			return (0);
		}
		if (!temp->next)
			break ;
		temp = temp->next;
	}
	temp->next = malloc(sizeof(t_node));
	temp = temp->next;
	i = 0;
	while (str[i] != ' ')
		i++;
	temp->content = ft_substr(str, 0, i);
	temp->next = NULL;
	return (0);
}
