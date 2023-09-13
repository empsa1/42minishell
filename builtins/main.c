/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:37:10 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/13 23:34:43 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
    t_data *data;
    t_node *temp;
    
    if (ac != 2 || !av || !envp)
        return(1);
    data = get_env(envp);
    data->exp = NULL;
    // env(data, NULL);
    export(data, av[1]);
    printf("%p\n", data->exp);
    // export(data, NULL);
    // env(data, NULL);
    // unset(data, av[1]);
    cleanup(data);
    return(0);
}