/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:41:40 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/13 09:40:12 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int echo(char *str)
{
    int i;

    i =    0;
    if (!ft_strncmp(str, "-n", 2))
    {
        if (!ft_strncmp(str, "-n ", 3))
            return(ft_putstr_fd(ft_strtrim(&str[2], " "), 1));
        while (str[2 + i])
        {
            if (str[2 + i] == 'n')
                i++;
            else if (str[2 + i] == ' ')
            {
                i++;
                break;
            }
            else
                return(ft_putstr_fd(str, 1));
            i++;
        }
        return(ft_putstr_fd(ft_strtrim(&str[2 + i], " "), 1));
    }
    return(ft_putendl_fd(ft_strtrim(str, " "), 1));
}

// int main(int ac, char **av)
// {
//     if (ac == 2)
//         return(echo(av[1]));
// }