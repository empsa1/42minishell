/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:38:59 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/21 17:20:12 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int mini_heredoc(char *eof)
{
    char *str;
    char *out;
    char *heredoc = "";
    char *eofile = ft_strjoin(eof, "\0");

    int fd = open("heredoc_163465", O_CREAT | O_WRONLY | O_TRUNC, 0664);
    printf("I-m HEREDORC\n");
        while (ft_strncmp(heredoc, eofile, ft_strlen(eofile) + 1))
        {
            heredoc = readline("heredoc>");
            out = ft_strjoin(heredoc, "\n");
            if (heredoc && ft_strncmp(heredoc, eofile, ft_strlen(eofile) + 1))
                write(fd, out, ft_strlen(out));
            free(out);
        }
        while ((str = get_next_line(fd)))
            printf("%s\n", str);
    close(fd);
    unlink("heredoc_163465");
    return(0);
}

int main(int ac, char **av)
{
    if (ac < 2)
        return (1);
    mini_heredoc(av[1]);
}
