/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:41:40 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/12 15:51:34 by anda-cun         ###   ########.fr       */
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
            return (printf("%s", ft_strtrim(&str[2], " ")));
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
                return (printf("%s", str));
            i++;
        }
        return (printf("%s", ft_strtrim(&str[2 + i], " ")));
    }
    else
        return (printf("%s\n", ft_strtrim(str, " ")));
    return (0);
}

// int main()
// {
//     echo("-n nnnnaaaa");
// }