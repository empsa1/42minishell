/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 19:52:36 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/13 22:49:02 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* TO CLEAN
*   data->path
*   data->env
*/

#include "includes/minishell.h"

void cleanup(t_data *data)
{
    t_node *temp;

    while (data->env)
    {
        temp = data->env;
        free(data->env->content);
        data->env = data->env->next;
        free(temp);
    }
    free(data);
}