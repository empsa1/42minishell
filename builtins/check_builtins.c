/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:04:34 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/26 21:16:21 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(t_data *data, char **args)
{
	int		(*fun_ptr_arr[7])(t_data *, char **);
	char	*functions[7];
	int		i;

	functions[0] = "cd";
	functions[1] = "echo";
	functions[2] = "env";
	functions[3] = "export";
	functions[4] = "pwd";
	functions[5] = "unset";
    functions[6] = "exit";
	fun_ptr_arr[0] = cd;
	fun_ptr_arr[1] = echo;
	fun_ptr_arr[2] = env;
	fun_ptr_arr[3] = export;
	fun_ptr_arr[4] = pwd;
	fun_ptr_arr[5] = unset;
	fun_ptr_arr[6] = exit_builtin;
	(void)data;
	i = -1;
	while (++i < 7)
	{
		if (!ft_strncmp(functions[i], *args, ft_strlen(functions[i]))
			&& !args[0][ft_strlen(functions[i])])
		{
			(*fun_ptr_arr[i])(data, &args[1]);
			return (1);
		}
	}
	return (0);
}
