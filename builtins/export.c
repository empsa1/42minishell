/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:56:45 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/14 17:37:42 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_node(t_node *temp, char *str)
{
	int	i;

	printf("Here\n");
	temp->next = malloc(sizeof(t_node));
	temp = temp->next;
	i = 0;
	temp->content = ft_strdup(str);
	temp->next = NULL;
}

// int	get_len(char *str)
// {
// 	int	len;
// 	int	equal;

// 	equal = 0;
// 	len = 0;
// 	while (str[len])
// 	{
// 		if (str[len] == '=' && str[len + 1])
// 		{
// 			equal = 1;
// 			if (str[len + 1] && str[len + 1] == ' ')
// 				break ;
// 		}
// 		len++;
// 	}
// 	if (equal)
// 		return (len);
// 	return (0);
// }

int print_export(t_data *data)
{
	t_node *temp;
	
	temp = data->env;
	while (temp)
	{
		printf("declare -x %s\n", temp->content);
		temp = temp->next;
	}
	return(0);
}

int get_len(char *str)
{
	int len;
	len = 0;
	if (get_length_to_char(str, '='))
		return (ft_strlen(str));
	return(0);
}

int	export(t_data *data, char *str)
{
	t_node	*temp;
	int		len;

	if (!str)
		return (print_export(data));
	len = get_len(str);
	if (!len)
		return(printf("add to export vars\n"));
		// return(add_to_export_vars(str));
	if (!len)
		return (0);
	temp = data->env;
	while (temp)
	{
		if (!ft_strncmp(temp->content, str, get_length_to_char(str, '=')))
		{
			free(temp->content);
			temp->content = ft_strdup(str);
			return (0);
		}
		if (!temp->next)
			break ;
		temp = temp->next;
	}
	add_node(temp, str);
	return (0);
}
