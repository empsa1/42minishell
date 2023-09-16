/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:37:10 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/16 23:54:56 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
    t_data *data;
    // t_node *temp;
    
    // if (ac == 1 || !av || !envp)
    //     return(1);
    // if (<K>av == NULL;
    // int fd = open("file", O_RDONLY);
    // dup2(fd, STDIN_FILENO);
    // char *exec[] = { "wc", "-l", NULL};
    // execve("/usr/bin/wc", exec, NULL);
    data = malloc(sizeof(t_data));
    data->exported_vars = malloc(sizeof(t_pair));
    data->exported_vars->key = NULL;
    data->exported_vars->value = NULL;
    data->exported_vars->next = NULL;
    data->env = get_env(envp);
    // env(data->env, NULL);
    // data->exported_vars = malloc(sizeof(t_node));
    // data->exported_vars->content = NULL;
    // data->exported_vars->next = NULL;
    export(data->env, data->exported_vars, &av[1]);
    export(data->env, data->exported_vars, NULL);
    env(data->env, data->exported_vars, NULL);
    // export(data->env, data->exported_vars, NULL);
    // print_exported(data->exported_vars);
    // env(data, NULL);
    // printf("%p\n", data->exp);
    // // export(data, NULL);
    // // env(data, NULL);
    // // unset(data, av[1]);
    cleanup(data);
    return(0);
}