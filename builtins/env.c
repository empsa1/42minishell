/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:32:07 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/10 20:35:02 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env(t_data *data, char *str)
{
    t_env *temp;
    
	if (str)
	{
		print_error("minishell: env: syntax error\n");
		return (-1);
	}
	temp = data->env;
	while (temp->next)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
}