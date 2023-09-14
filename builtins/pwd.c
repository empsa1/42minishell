/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:52:45 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/14 10:05:34 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int pwd(void)
{
    char buf[PATH_MAX];
    
    if (!getcwd(buf, PATH_MAX))
        perror("pwd:");
    ft_putendl_fd(buf, 2);
    return(0);
}