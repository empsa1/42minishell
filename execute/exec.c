/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:05:45 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/09 18:14:20 by anda-cun         ###   ########.fr       */
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
            print_error("minishell: command not found: ");
            print_error(str[0]);
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