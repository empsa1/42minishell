/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:37:10 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/15 15:47:34 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
    t_data *data;
    // t_node *temp;
    
    if (ac != 2 || !av || !envp)
        return(1);
    // int fd[2];
    // pipe(fd);
    // int fd = open("file", O_RDONLY);
    // dup2(fd, STDIN_FILENO);
    // close(fd[0]);
    // fd[1] = open("file", O_RDONLY);
    // char *exec[] = { "ls", "filea", "file2a", NULL};
    // execve("/usr/bin/ls", exec, NULL);
    // export(data, av[1]);
    data = get_env(envp);
    data->exported_vars = malloc(sizeof(t_node));
    data->exported_vars->content = NULL;
    data->exported_vars->next = NULL;
    export(data, av[1]);
    export(data, NULL);
    // print_exported(data->exported_vars);
    printf("ENVVVVVV\n");
    env(data, NULL);
    // printf("%p\n", data->exp);
    // // export(data, NULL);
    // // env(data, NULL);
    // // unset(data, av[1]);
    cleanup(data);
    return(0);
}