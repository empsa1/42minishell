/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 06:47:38 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/26 05:28:17 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env(t_pair *pair)
{
	t_pair	*temp;

	while (pair)
	{
		temp = pair;
		free(pair->key);
		free(pair->value);
		pair = pair->next;
		free(temp);
	}
}

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i] != NULL)
		free(path[i++]);
	free(path);
}

void	free_data(t_data *data)
{
	free(data->pid);
	free(data->pipes.next);
	free_env(data->env);
	free_path(data->path);
}