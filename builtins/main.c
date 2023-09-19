/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:37:10 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/17 23:03:08 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data *data;
	// t_node *temp;

	// if (ac == 1 || !av || !envp)
	//     return(1);
    // 

	data = malloc(sizeof(t_data));
	data->exported_vars = malloc(sizeof(t_pair));
	data->exported_vars->key = NULL;
	data->exported_vars->value = NULL;
	data->exported_vars->next = NULL;
	data->env = get_env(envp);
    char *export_v[4] = {"ui", "ei", "ai"};
	export(data->env, data->exported_vars, &av[1]);
	// export(data->env, data->exported_vars, NULL);
	unset(data, export_v);
    export(data->env, data->exported_vars, NULL);
	cleanup(data);
	return (0);
}