/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:46:54 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/14 13:01:34 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief create linked list of environment variables, and linked list of exported variables
 * 
 * @param envp 
 * @return t_data* 
 */

// void get_export(t_data *data)
// {
//     int i;
//     t_node *exp_ptr;
//     t_node *env_ptr;
    
//     i = 0;
//     env_ptr = data->env;
//     exp_ptr = data->exp;
//     i = 0;
//     while (env_ptr)
//     {
//         exp_ptr = env_ptr;
//         if (!exp_ptr)
//         {
//             ft_putendl_fd("Error allocating memory\n", 2);
//             break;
//         }
//         if (ft_strncmp(exp_ptr->content, env_ptr->next->content, ft_strlen(exp_ptr->content)))
//             env_ptr = env_ptr->next;
//         else
//         {
//             printf("%s\n", exp_ptr->content);
//             exp_ptr->next = NULL;
//             i++;
//         }
//     }
// }

t_data *get_env(char **envp)
{
    int i;
    t_data *data;
    t_node *env_ptr;

    data = malloc(sizeof(t_data));
    i = 0;
    data->env = malloc(sizeof(t_node));
    env_ptr = data->env;
    while (envp[i])
        i++;
    i = 0;
    while (envp[i])
    {
        if (!env_ptr)
        {
            ft_putendl_fd("Error allocating memory\n", 2);
            break;
        }
        env_ptr->content = ft_strdup(envp[i]);
        if (envp[i + 1])
        {
            env_ptr->next = malloc(sizeof(t_node));
            env_ptr = env_ptr->next;
        }
        else
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