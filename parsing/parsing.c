#include "minishell.h"

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

char    *treat_str(char *line)
{
    int i;
    int j = 0;
    char aspas;
    char *newline;

    newline = malloc(ft_strlen(line) * 2);
    i =     -1;
    aspas = 0;
    while (line[++i] != '\0')
    {
        if (!aspas && (line[i] == '"' || line[i] == '\''))
        {    
            newline[j++] = 2;
            aspas = line[i];
            newline[j++] = aspas;
        }
        else if (line[i] == aspas)
        {   
            newline[j++] = aspas;
            newline[j++] = 2;
            aspas = 0;
        }
        else
        {
            if (aspas == 0 && line[i] == ' ')
            line[i] = 2;
            if (aspas == 0 && line[i] == '|')
                newline[j++] = 2;
            newline[j++] = line[i];
            if (aspas == 0 && line[i] == '|')
                newline[j++] = 2;
        }
  
    }
    newline[j] = 0;
    return (newline);
}

int ft_strleni(char **splitter, int i)
{
    int size;

    size = 0;
    while (splitter[i++] != NULL)
        size++;
    return (size);
}

void parsing(t_command_list *cmd_lst, char **splitter, int i)
{

    cmd_lst = malloc(sizeof(t_command_list));
    cmd_lst->arg = malloc(sizeof(t_argwc) * ft_strleni(splitter, i));
    // if (!is_valid_command(splitter[i++]))
    //     exit(-1);
    cmd_lst->arg[0].token = splitter[0];
    cmd_lst->arg[0].type = token(splitter[0], 0);
    while (splitter[i] && !zcmp(splitter[i], "|") && !zcmp(splitter[i], ";"))
    {
        cmd_lst->arg[i].token = splitter[i];
        cmd_lst->arg[i].type = token(splitter[i], 0);
        i++;
        
    }
    //debug(NULL, NULL, &cmd_lst);
    if (zcmp(splitter[i], "|"))
    {
        t_command_list *cmd_newlst;
        cmd_lst->next = cmd_newlst;
        parsing(cmd_newlst, splitter, i);
    }
    if (zcmp(splitter[i], ";"))
    {
        cmd_lst->next = NULL;
        return ;
    }
    cmd_lst->next = NULL;
}

//{Tester 1} echo "dsgasd ' fdsf 'fds daf"dfadf"    dddw"