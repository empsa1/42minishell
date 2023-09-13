/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:37:10 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/13 16:08:51 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
    t_data *data;
    if (ac != 2 || !av || !envp)
        return(1);
    data = get_env(envp);
    // env(data, NULL);
    export(data, av[1]);
    // env(data, NULL);
    unset(data, "ai");
    env(data, NULL);
    return(0);
}