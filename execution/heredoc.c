/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:38:59 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/22 06:17:13 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	mini_heredoc(char *eof)
{
	char	*out;
	char	*heredoc;
	char	*eofile;
	int		fd;

	heredoc = "";
	eofile = ft_strjoin(eof, "\0");
	fd = open("heredoc_163465", O_CREAT | O_WRONLY | O_TRUNC, 0664);
	printf("heredoc fd: %d\n", fd);
	while (ft_strncmp(heredoc, eofile, ft_strlen(eofile) + 1))
	{
		heredoc = readline(">");
		out = ft_strjoin(heredoc, "\n");
		if (heredoc && ft_strncmp(heredoc, eofile, ft_strlen(eofile) + 1))
			write(fd, out, ft_strlen(out));
		free(out);
	}
    close(fd);
    return (0);
}

// int main(int ac, char **av)
// {
//     if (ac < 2)
//         return (1);
//     mini_heredoc(av[1]);
// }
