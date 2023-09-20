/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:38:59 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/20 17:23:38 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int mini_heredoc()
{
    if (unlink("../help") == -1)
        printf("Error removing temp file\n");
    char *eof = "pqp";
    char *heredoc = "";
    char *eofile = ft_strjoin(eof, "\0");

    int fd = open("help", O_CREAT | O_WRONLY | O_APPEND, 0664);
    printf("I-m HEREDORC\n");
        while (strncmp(heredoc, eofile, 4))
        {
            char *out = ft_strjoin(heredoc, "\n");
            if (heredoc)
                write(fd, out, ft_strlen(out));
            heredoc = readline("heredoc>");
            free(out);
        }
        close(fd);
    return(0);
}