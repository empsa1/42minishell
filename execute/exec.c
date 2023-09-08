/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:05:45 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/08 17:31:39 by anda-cun         ###   ########.fr       */
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
        execve(str[0], str, NULL);
    }
    return (0);
}

int main()
{
    char **str;

    str = ft_split("/usr/bin/ls -l", ' ');
    exec(str);
}