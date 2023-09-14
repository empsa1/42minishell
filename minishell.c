/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eportela <eportela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:47:26 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/14 10:45:17 by eportela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int create_executor(char *command)
{
    if (fork() == 0)
    {
        signal(SIGINT, sigint_handler);
        exec(&command);
        kill(getpid(), SIGSEGV);
    }
    return (0);
}

void init(t_data *data, char **envp)
{
    int i;
    data->stdin = dup(STDIN_FILENO);
    data->stdout = dup(STDOUT_FILENO);
    data->stderr = dup(STDERR_FILENO);
    i = -1;
    while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			data->path = ft_split(&envp[i][5], ':');
	}
    getcwd(data->cwd, PATH_MAX);
}

int main(int ac, char **av, char **envp)
{
    (void)av;
    if (ac != 1)
        return(ft_putstr_fd("Error: Too many arguments\n", 1));
    t_data data;
    init(&data, envp);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, terminal_prompt);
    while (1)
    {
        char *line = readline("minishell$>");
        if (line != NULL && *line)
            add_history(line);
            if (ft_strtrim(line, " \n\t\r\b") != NULL && parsing(line))
                    create_executor(line); 
        free(line);
    }
    return (0);
}