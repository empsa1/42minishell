#include "minishell.h"

void    iterator(char *line)
{
    int i = 0;
    while (line[i] != '\0')
    {
        printf("Index %d-> {%c}; ", i, line[i]);
        i++;
    }
    printf("\n");
}

int token(char *line, int i)
{
    if (line[i] == '|')
        return PIPE;
    if (line[i] == '>')
    {
        if (line[i + 1] && line[i + 1]  == '>')
            return (APPEND);
        else
            return (OUT);
    }
    if (line[i] == '<')
    {
        if (line[i + 1] && line[i + 1] == '<')
            return (HEREDOC);
        else
            return (IN);
    }
    if (line[i] == ';')
        return (END);
    else
        return (STR);
}

int ft_strleni(char **splitter, int i)
{
    int size;

    size = 0;
    while (splitter[i] && !z_cmp(splitter[i++], "|"))
        size++;
    return (size);
}
