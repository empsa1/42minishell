/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleardata.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eportela <eportela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:26:43 by eportela          #+#    #+#             */
/*   Updated: 2023/09/21 15:26:43 by eportela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//clears previous cmd_lst linked nodes
void    free_linkedlst(t_command_list *cmd_lst)
{
    printf("{free_linkedlst()} Inside function\n");
    t_command_list *to_clean;
        to_clean = cmd_lst->next;
    printf("{free_linkedlst} Out of loop holder\n");
    printf("Last node of Linked-list: %p\n", to_clean);
    free(cmd_lst);
    if (to_clean)
        free_linkedlst(to_clean);
}

void    free_all(t_command_list *cmd_lst, char *line, char *changes, char **splitter)
{
    free_linkedlst(cmd_lst);
    free(changes);
    free(splitter);
    free(line);
}