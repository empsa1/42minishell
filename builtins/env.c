/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:32:07 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/15 15:35:27 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief	print env variables + exported variables with '=' sign, unordered
 *
 * @param data
 * @param str
 * @return int
 */

int env(t_data *data, char *str)
{
	t_node *temp;

	if (str)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": no such file or directory", 2);
		return (-1);
	}
	print_nodes(data->env);
	// print_exported(data->exported_vars);
	// temp = data->exported_vars;
	// while (temp)
	// {
	// 	printf("%s\n", temp->content);
	// // if (ft_strchr(temp->content, '='))
	// // 	printf("%s\n", temp->content);
	// 	temp = temp->next;
	// }
	return (0);
}