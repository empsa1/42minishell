#include "minishell.h"

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
//echo "dsgasd ' fdsf 'fds daf"dfadf"    dddw"
// void    parsing(char *line)
// {
//     int i;
//     char **cmd;
//     t_command_list cmd_lst;

//     i = 1;
//     cmd = ft_split(treat_str(line));

//     while (cmd[i])
//     {
        
//     }
// }

// int main(int argc, char **argv)
// {
//     int i = 0;
//     printf("Line to be treated: %s\n", argv[1]);
//     char **newstring = ft_split(treat_str(argv[1]), 2);
//     while (newstring[i])
//     {
//         printf("String: %s\n", newstring[i]);
//         i++;
//     }
//     printf("Line treated: %s\n",treat_str(argv[1]));
// }