/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:05:45 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/09 17:38:30 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int exec(char **str)
{
    int pid;
    
    pid = fork();
    if (pid == -1)
        return (-1);
    if (pid == 0)
    {
        if (execve(str[0], str, NULL) == -1)
        {
            printf("%s\n", str[0]);
            print_error("minishell: command not found: ", str[0]);
        }
    }
    return (0);
}

int main()
{
    char **str;

    str = ft_split("/usr/bin/laz ai", ' ');
    exec(str);
}