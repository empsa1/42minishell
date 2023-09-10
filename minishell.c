/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:47:26 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/10 17:08:21 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
    // HIST_ENTRY **history_list;

    (void)av;
    if (ac != 1)
        return(print_error("Error: Too many arguments\n"));
    t_data data;
    init(&data, envp);
    if (fork() == 0)
    {
        arm_signals();
        while (1)
        {
            char *line = readline("minishell$>");
            printf("%s\n", line);
            if (*line)
            add_history(line);
            // parsing(line);
            // exec(&line);
            free(line);
        }
    }
    else
    {
        signal(SIGINT, SIG_IGN);
    }
    return (0);
}