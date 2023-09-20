/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:47:26 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/20 17:27:18 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
    data->pipes.open = 0;
	data->pipes.next = malloc(sizeof(t_pipe));
	data->pipes.next->open = 0;
	data->pipes.next->next = &data->pipes;
	getcwd(data->cwd, PATH_MAX);
}

int	main(int ac, char **av, char **envp)
{
    (void)av;
    char *changes;
    char **splitter;
    t_command_list cmd_lst;

    if (ac != 1)
        return(ft_putstr_fd("Error: Too many arguments\n", 1));
    t_data data;
    init(&data, envp);
    // signal(SIGQUIT, SIG_IGN);
    // signal(SIGINT, terminal_prompt);
    while (1)
    {
        char *line = readline("minishell$>");
        if (line != NULL && *line)
        {
            add_history(line);
            changes = treat_str(line);
            splitter = ft_split(changes, 2);
            parsing(&cmd_lst, splitter, 0);
            // check_cmd(&cmd_lst, &data.pipes);
            // printf("%s\n", cmd_lst->arg->token);
            //debug(splliter, changes, NULL);
            //create_executor(parsing(line));
            // free_all(&cmd_lst, line, changes, splitter);
        }
    }
    return (0);
}