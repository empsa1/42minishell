/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:46:54 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/14 12:09:08 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief create linked list of environment variables, and linked list of exported variables
 * 
 * @param envp 
 * @return t_data* 
 */

void get_export(t_data *data, envp)
{
    int i;
    t_node *exp_ptr;
    t_node *env_ptr;
    
    i = 0;
    exp_ptr = data->exp;
    i = 0;
    while (envp[i])
    {
        exp_ptr = malloc(sizeof(t_node));
        if (!exp_ptr)
        {
            ft_putendl_fd("Error allocating memory\n", 2);
            break;
        }
        exp_ptr->content = ft_strdup(envp[i]);
        printf("%s\n", exp_ptr->content);
        exp_ptr->next = NULL;
        i++;
    }
}

t_data *get_env(char **envp)
{
    int i;
    t_data *data;
    t_node *env_ptr;

    data = malloc(sizeof(t_data));
    i = 0;
    while (envp[i])
        i++;
    env_ptr = data->exp;
    i = 0;
    while (envp[i])
    {
        env_ptr = malloc(sizeof(t_node));
        if (!env_ptr)
        {
            ft_putendl_fd("Error allocating memory\n", 2);
            break;
        }
        env_ptr->content = ft_strdup(envp[i]);
        env_ptr->next = NULL;
        i++;
    }
    get_export(data, envp);
    return (data);
}

// int main(int ac, char **av, char **envp)
// {
//     if (!ac || !av)
//         printf("Error\n");
//     get_env(envp);
// }