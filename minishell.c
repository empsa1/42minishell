#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "./libft/libft.h"

int main()
{
    char *heredoc = "";
    while (1)
    {
        char *line = readline("minishell$>");
        printf("%s\n", line);
        if (*line)
            add_history(line);
        if (!ft_strncmp(line, "<<", 2))
        {
            while (strncmp(heredoc, "EOF", 3))
                heredoc = readline("heredoc>");
        }
        free(line);
    }
}