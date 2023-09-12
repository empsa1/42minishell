/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:47:26 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/12 10:21:34 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int create_executor(char *command)
{
    printf("Inside forking child process %s\n", command);
    signal(SIGINT, sigint_handler);
    // exec(&command);
    printf("GOing to kill it");
    kill(SIGINT, getpid());
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
    // HIST_ENTRY **history_list;
    //char *buffer = NULL;
    (void)av;
    printf("%d\n", getpid());
    if (ac != 1)
        return(print_error("Error: Too many arguments\n"));
    t_data data;
    init(&data, envp);
    signal(SIGINT, sigint_handler_parent); //makes parent process ignore SIGINT INPUT
    //signal(SIGQUIT, sigEOF_handler);
    while (1)
    {
        printf("Another Rotation\n");
        char *line = readline("minishell$>");
        if (*line)
        {
            if (ft_strtrim(line, " \n\t\r\b") != NULL)
                add_history(line);
            if (fork() == 0)
            {
                //if (parsing(line) == valid);
                    create_executor(line);
                printf("PID: %d, Command: %s\n", getpid(), line);
            }
            else 
            {   
                wait(NULL); //WAITS FOR CHILD PROCESS TO DIE BEFORE CONTINUING
                printf("Inside if line condition in parent process\n");
                //read(STDIN_FILENO, buffer, BUFSIZ);
                //printf("Buffer in stdin: %s\n", buffer);
                // if (buffer == NULL)
                //     sigEOF_handler(1);  
            }
        }
        free(line);
    }
    return (0);
}