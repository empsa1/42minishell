/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:53:27 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/10 18:00:26 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int cd (t_data *data, char *str)
{
    t_env *temp;
    char *oldpwd;
    char	buf[PATH_MAX];

    temp = data->env;
	getcwd(buf, PATH_MAX);
    oldpwd = ft_strdup(buf);
    expand_path(str, buf);
    if (chdir(buf) == -1)
	{
		printf("cd: %s: %s\n", strerror(errno), str);
		return (errno);
	}
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
    temp = data->env;
    while (temp->next)
    {
        printf("%s\n", temp->content);
        temp = temp->next;
    }
}
// int	main(void)
// {
// 	cd("test/../execute/../test/test2/./test3/./../../");
// }