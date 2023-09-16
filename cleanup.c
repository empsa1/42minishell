/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 19:52:36 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/16 23:46:47 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* TO CLEAN
*   data->path
*   data->env
*/

#include "includes/minishell.h"

void cleanup(t_data *data)
{

    free_pairs(data->env);
    free_pairs(data->exported_vars);
    free(data);
}