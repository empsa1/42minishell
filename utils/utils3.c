/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eportela <eportela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:26:35 by eportela          #+#    #+#             */
/*   Updated: 2023/09/21 15:26:35 by eportela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_struct(t_command_list *lst)
{
    int i;

    i = 0;
    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
    while (lst)
    {
        while (lst->arg[i].token != NULL)
        {
            printf("{%p} Index: {%d}-> Token: {%s}; Type: {%d}\n", lst, i, lst->arg[i].token, lst->arg[i].type);
            i++;
        }
        i = 0;
        lst = lst->next;
    }
}

int z_cmp(char *str, char *cmp)
{
    int i;

    i = 0;
    while (str[i] != '\0' && cmp[i] != '\0')
    {
        if (str[i] != cmp[i])
            return 0;
        i++;
    }
    if (str[i] != '\0' || cmp[i] != '\0')
        return 0;
    return 1;
}