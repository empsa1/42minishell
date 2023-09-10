/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:41:40 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/10 11:55:52 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int echo(char *str)
{
    if (!str)
    {
        print_error("minishell: echo: syntax error\n");
        return (-1);
    }
    if (!ft_strncmp(str, "-n", 2))
        printf("%s", ft_strtrim(&str[2], " "));
    else
        printf("%s\n", ft_strtrim(str, " "));
}

// int main()
// {
//     echo("");
// }