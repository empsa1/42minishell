/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:56:45 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/13 16:00:56 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export(t_data *data, char *str)
{
	t_env	*temp;
	int		i;

	i = -1;
	while (str[++i] && str[i] != ' ')
		if (str[i] == '=' && str[i + 1] && str[i + 1] != ' ')
			break ;
	if (str[i] != '=')
		return (0);
	temp = data->env;
	while (temp->next)
	{
		if (!ft_strncmp(temp->content, str, i + 1))
		{
			free(temp->content);
			temp->content = ft_strdup(str);
			return(0);
		}
		temp = temp->next;
	}
	temp->next = malloc(sizeof(t_env));
	temp = temp->next;
	i = 0;
	while (str[i] != ' ')
		i++;
	temp->content = ft_substr(str, 0, i);
	temp->next = NULL;
	return (0);
}