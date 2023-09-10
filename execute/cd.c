/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:53:27 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/10 13:03:12 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int cd(char *str)
{
    char buf[PATH_MAX];
    int i;
    int j;
    
    i = 0;
    j = 0;
    getcwd(buf, PATH_MAX);
    while (buf[i])
        i++;
    if (buf[i] != '/')
        buf[i++] = '/';
    while (str[j])
    {
        if (!ft_strncmp(&str[j], "/.", 2) && str[j + 2] != '.')
            j += 2;
        else if (!ft_strncmp(&str[j], "/..", 3))
        {
            printf("%s\n", &str[j]);
            while (buf[i] != '/')
                buf[i--] = 0;
            printf("buf[%d]: %s\n", i, &buf[i]);
            j += 2;
        }
        buf[i++] = str[j++];
    }
    buf[i] = '\0';
    printf("%s\n", buf);
    // if (*str == '/' || *str != '.')
    // {
    //     if (chdir(str) == -1)
    //     {
    //         printf("cd: %s: %s\n", strerror(errno), str);
    //         return(errno);
    //     }
    // }
}

int main()
{
    cd("test/../.././");
}