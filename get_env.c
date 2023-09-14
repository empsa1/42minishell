/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:46:54 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/14 16:01:10 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief create linked list of environment variables, and linked list of exported variables
 *
 * @param envp
 * @return t_data*
 */

void get_export(t_data *data)
{
    t_node *exp_ptr;
    t_node *env_ptr;

    env_ptr = data->env;
    data->exp = malloc(sizeof(t_node));
    exp_ptr = data->exp;
    exp_ptr->content = env_ptr->content;
    while (env_ptr)
    {
        printf("%s\n", env_ptr->content);
        if (env_ptr->next)
        {
            if (ft_strncmp(exp_ptr->content, env_ptr->next->content, ft_strlen(exp_ptr->content)) > 0)
            {
                exp_ptr->content = env_ptr->next->content;
                if (exp_ptr->next)
                    free(exp_ptr->next);
                exp_ptr->next = NULL;
                exp_ptr = data->exp;
                env_ptr = data->env;
            }
            else
            {
                if (!exp_ptr->next)
                    exp_ptr->next = malloc(sizeof(t_node));
                exp_ptr = exp_ptr->next;
                // exp_ptr->content = env_ptr->next->content;
                if (!exp_ptr->next)
                    exp_ptr->next = NULL;
                env_ptr = env_ptr->next;
            }
        }
    }
    exp_ptr = data->exp;
    // while (exp_ptr)
    // {
    //     printf("%s\n", exp_ptr->content);
    //     exp_ptr = exp_ptr->next;
    // }
}

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
    // get_export(data);
    return (data);
}

// int main(int ac, char **av, char **envp)
// {
//     if (!ac || !av)
//         printf("Error\n");
//     get_env(envp);
// }