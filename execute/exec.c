/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:05:45 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/12 20:12:23 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int exec(char **str)
{
    int pid;
    int wstatus;
    
    pid = fork();
    if (pid == -1)
    {
        print_error("Error forking\n");
        return (1);
    }
    if (pid == 0)
    {
        if (execve(str[0], str, NULL) == -1)
        {
            ft_putendl_fd("minishell: command not found: ", 2);
            ft_putendl_fd(str[0], 2);
        }
    }
    else
        waitpid(-1, &wstatus, 0);
    
    return (0);
}

int main()
{
    char **str;

    str = ft_split("/usr/bin/lsz ai", ' ');
    exec(str);
}