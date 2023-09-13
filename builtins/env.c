/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:32:07 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/13 22:49:38 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env(t_data *data, char *str)
{
    t_node *temp;
    
	if (str)
	{
		ft_putendl_fd("minishell: env: syntax error\n", 2);
		return (-1);
	}
	temp = data->env;
	while (temp->next)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
	printf("%s\n", temp->content);
	return(0);
}