/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 21:07:29 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/27 15:15:10 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_builtin(t_data *data, char **str)
{
	int ret;

	if (!data->pipes.open)
	{
		ft_putendl_fd("exit", 1);
		data->exit = 1;
	}
	else
		data->exit = 0;
	if (!str[0])
		return (data->exit_status);
	ret = ft_atoi(str[0]);
	data->exit_status = ret % 256;
	return (data->exit_status);
}