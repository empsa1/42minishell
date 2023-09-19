/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:25:47 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/18 19:06:49 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_pair *get_env(char **envp)
{
    int i;
    t_pair *node;
    t_pair *temp_node;

    i = 0;
    node = malloc(sizeof(t_pair));
    temp_node = node;
    while (envp[i])
    {
        temp_node->key = ft_substr(envp[i], 0, get_length_to_char(envp[i], '=') + 1);
        temp_node->value = ft_strdup(ft_strchr(envp[i], '=') + 1);
        if (envp[i + 1])
        {
            temp_node->next = malloc(sizeof(t_pair));
            temp_node = temp_node->next;
        }
        else
        {
            temp_node->next = NULL;   
            break;
        }
        i++;
    }
    return(node);
}

// int main(int ac, char **av, char **envp)
// {
//     t_data *data;
    
//     if (!ac || !av)
//         return(1);
//     data = malloc(sizeof(t_data));
//     data->env = get_env(envp);
//     t_pair *temp;
//     while (data->env)
//     {
//         temp = data->env;
//         free(data->env->key);
//         free(data->env->value);
//         data->env = data->env->next;
//         free(temp);
//     }
//     free(data);
// }