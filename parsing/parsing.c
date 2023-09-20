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
    while (splitter[i] != NULL && !zcmp(splitter[i++], "|"))
        size++;
    printf("{ft_strleni()} Size result: %d\n}", size);
    return (size);
}

void parsing(t_command_list *cmd_lst, char **splitter, int i)
{
    printf("{parsing()} Going to malloc for the struct\n");
    cmd_lst = malloc(sizeof(t_command_list));
    cmd_lst->arg = malloc(sizeof(t_argwc) * ft_strleni(splitter, i));
    printf("{parsing()} success malloc for the struct\n");
    // if (!is_valid_command(splitter[i++]))
    //     exit(-1);
    while (splitter[i] && !zcmp(splitter[i], "|") && !zcmp(splitter[i], ";"))
    {
        printf("{parsing()} Inside loop!\n");
        cmd_lst->arg[i].token = splitter[i];
        cmd_lst->arg[i].type = token(splitter[i], 0);
        printf("{parsing()} Token Argument: %s\n{parsing()} Token Type: %d\n",cmd_lst->arg[i].token, cmd_lst->arg[i].type);
        i++; 
    }
    //debug(NULL, NULL, &cmd_lst);
    printf("{parsing()} Out of the loop\n");
    if (splitter[i] && zcmp(splitter[i], "|"))
    {
        printf("{parsing()} Inside Pipe Condition!\n");
        t_command_list *cmd_newlst;
        cmd_newlst = NULL;
        cmd_lst->next = cmd_newlst;
        printf("{parsing()} Going parsing again\n");
        parsing(cmd_newlst, splitter, ++i);
    }
    else if (splitter[i] && zcmp(splitter[i], ";"))
    {
        printf("{parsing()} Inside END Condition!\n");
        cmd_lst->next = NULL;
        return ;
    }else{
    printf("{parsing()} Going to assign NULL to next since the parsing ended\n");
    cmd_lst->next = NULL;
    printf("{parsing()} NULL was assigned leaving parsing()\n");
    }
}

//{Tester 1} echo "dsgasd ' fdsf 'fds daf"dfadf"    dddw"