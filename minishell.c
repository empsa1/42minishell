#include "minishell.h"

void init(t_data *data, char **envp)
{
    int i = 0;
    data->stdin = dup(STDIN_FILENO);
    data->stdout = dup(STDOUT_FILENO);
    data->stderr = dup(STDERR_FILENO);
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
        return(print_error("Error: Too many arguments\n"));
    t_data data;

    init(&data, envp);
    while (1)
    {
        char *line = readline("minishell$>");
        printf("%s\n", line);
        if (*line)
            add_history(line);
        // parsing(line);
        // exec(line);
        free(line);
    }
}