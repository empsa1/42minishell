/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 19:52:36 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/15 13:58:51 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* TO CLEAN
*   data->path
*   data->env
*/

#include "includes/minishell.h"

void cleanup(t_data *data)
{

    free_nodes(data->env);
    free_nodes(data->exported_vars);
    free(data);
}