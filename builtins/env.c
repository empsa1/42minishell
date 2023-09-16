/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:32:07 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/16 23:58:30 by anda-cun         ###   ########.fr       */
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

int env(t_pair *env, t_pair *exported_vars, char *str)
{
	t_pair *temp;

	if (str)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": too many args", 2);
		return (-1);
	}
	temp = exported_vars;
	print_pairs(env);
	while(temp)
	{
		if (ft_strchr(temp->key, '=') && *temp->value)
            printf("%s%s\n", temp->key, temp->value);
		temp = temp->next;
	}
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