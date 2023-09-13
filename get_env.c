/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:46:54 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/12 20:11:57 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void get_env(char **envp)
{
    int i;
    t_data data;
    t_env *env_ptr;

    i = 0;
    while (envp[i])
        i++;
    data.env = (t_env *)malloc(sizeof(t_env));
    if (!data.env)
        ft_putendl_fd("Error allocating memory\n", 2);
    env_ptr = data.env;
    i = 0;
    env_ptr->content = ft_strdup(envp[i++]);
    env_ptr ->next = NULL;
    while (envp[i])
    {
        env_ptr->next = malloc(sizeof(t_env));
        if (!env_ptr->next)
        {
            ft_putendl_fd("Error allocating memory\n", 2);
            break;
        }
        env_ptr = env_ptr->next;
        env_ptr->content = ft_strdup(envp[i]);
        env_ptr->next = NULL;
        i++;
    }
    cd(&data, "../");
    cd(&data, "./minishell/");
    cd(&data, "./includes");
    export(&data, "ai=u    dfgdfgdf"); // CHECK DOUBLES
    export(&data, "becabeca=aaa    dfgdfgdf");
    unset(&data, "LC_TIME");
}

int main(int ac, char **av, char **envp)
{
    if (!ac || !av)
        printf("Error\n");
    get_env(envp);
}