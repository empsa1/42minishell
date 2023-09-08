/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:05:45 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/08 16:54:42 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int exec(char *str)
{
    int pid = fork();
    if (pid == 0)
    {
        execve("ERASPDJOASD");
    }
}

void test()
{
    char *str;
    
    str = "/usr/bin/ls -a"
    exec(str);
}