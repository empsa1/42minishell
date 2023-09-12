/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:53:27 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/12 15:51:48 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int empty_path(t_data *data, char *buf)
{
    int i;
    t_env *temp;

    i = -1;
    printf("%s\n", buf);
    temp = data->env;
    while (temp->next)
    {
        if (!ft_strncmp(temp->content, "HOME=", 5))
        {
            while (temp->content[5 + ++i])
                buf[i] = temp->content[5 + i];
            while (buf[i])
                buf[i++] = 0;
        }
        temp = temp->next;
    }
    return (0);
}

int cd(t_data *data, char *str)
{
    t_env *temp;
    char *oldpwd;
    char buf[PATH_MAX];
    int i;

    i = 0;
    temp = data->env;
    getcwd(buf, PATH_MAX);
    oldpwd = ft_strdup(buf);
    if (!str)
        empty_path(data, buf);
    else if (*str == '-' && !str[1])
    {
        i = -1;
        while (temp->next)
        {
            if (!ft_strncmp(temp->content, "OLDPWD=", 7))
            {
                while (temp->content[7 + ++i])
                    buf[i] = temp->content[7 + i];
                while (buf[i])
                    buf[i] = 0;
            }
            temp = temp->next;
        }
    }
    else
        expand_path(str, buf);
    if (chdir(buf) == -1)
    {
        printf("cd: %s: %s\n", strerror(errno), str);
        return (errno);
    }
    temp = data->env;
    while (temp->next)
    {
        if (!ft_strncmp(temp->content, "OLDPWD=", 7))
        {
            free(temp->content);
            temp->content = ft_strjoin("OLDPWD=", oldpwd);
        }
        if (!ft_strncmp(temp->content, "PWD=", 4))
        {
            free(temp->content);
            temp->content = ft_strjoin("PWD=", buf);
        }
        temp = temp->next;
    }
    return (0);
}
// int	main(void)
// {
// 	cd("test/../execute/../test/test2/./test3/./../../");
// }