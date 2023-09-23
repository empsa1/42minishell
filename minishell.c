/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:47:26 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/22 17:14:17 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int create_executor(char *command)
// {
//     if (fork() == 0)
//     {
//         signal(SIGINT, sigint_handler);
//         exec(&command);
//         kill(getpid(), SIGSEGV);
//     }
//     return (0);
// }

void	init(t_data *data, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			data->path = ft_split(&envp[i][5], ':');
	}
	data->env = get_env(envp);
    data->exit_status = 0;
	data->pipes.next = malloc(sizeof(t_pipe));
	data->pipes.next->next = &data->pipes;
    data->heredoc = 0;
	getcwd(data->cwd, PATH_MAX);
}

int	main(int ac, char **av, char **envp)
{
	t_data data;
	char **splitter;
	char *changes;
	t_command_list *cmd_lst;
	if (ac != 1 || av[1])
		return (ft_putstr_fd("Error: Too many arguments\n", 1));
	init(&data, envp);
	// signal(SIGQUIT, SIG_IGN);
	// signal(SIGINT, terminal_prompt);
	while (1)
	{
		char *line = readline("minishell$>");
		if (line != NULL && *line)
		{
			add_history(line);
			if (!token_error(line))
			{
                cmd_lst = malloc(sizeof(t_command_list));
				changes = treat_str(line, 0, 0, 0);
				splitter = ft_split(changes, 2);
				int j = 0;
				printf("{main()} Treated: {%s}\n", line);
				while (splitter[j])
				{
					printf("{main()} Splitter %d: {%s}\n", j, splitter[j]);
					j++;
				}
				cmd_lst->arg = malloc(sizeof(t_arg) * (ft_strleni(splitter, 0) + 1));
				parsing(cmd_lst, splitter, 0);
				print_struct(cmd_lst);
                free_all(cmd_lst, changes, splitter);
                // check_cmd(&data, cmd_lst, &data.pipes);
			}
            free(line);
		}
	}
	return (0);
}