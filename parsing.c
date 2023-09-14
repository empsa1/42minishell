#include "minishell.h"

int is_valid_command(char* command)
{
    return (0);
}

int   catch_flags(t_command to_exec, char* line, int index)
{
    return (index);
}

t_command *parsing(char *line)
{
    int i;
    int j;
    int temp;
    t_command *to_exec;

    j = 0;
    i = 0;
    temp = 0;
    to_exec = malloc(sizeof(t_command));
    to_exec[j].valid = 0;
    while (line[i] != '\0')
    {
        temp = i;
        while (line[i] != " ")
            i++;
        to_exec[j].cmd[0] = ft_substr(line, temp, i);
        if (!is_valid_command(to_exec[j].cmd[0]))
        {
            to_exec[j].valid = 1;
            return (to_exec);
        }
        i = catch_flags(to_exec[j],line, i);
        if (line[i] == '|')
            to_exec[j].next = &(to_exec[++j]);
        else
            convert_rest(line, i);
    }
    return (to_exec);
}