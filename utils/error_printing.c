/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:54:19 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/18 19:06:32 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_file_error(char *s1, char *s2)
{
	ft_putstr_fd(s1, 2);
	ft_putchar_fd('"', 2);
	ft_putstr_fd(s2, 2);
	ft_putendl_fd("\": No such file or directory", 2);
	return (2);
}

int	print_syntax_error(char c)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (!c)
		ft_putstr_fd("newline", 2);
	else
		ft_putchar_fd(c, 2);
	ft_putendl_fd("'", 2);
	return (2);
}
