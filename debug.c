#include "minishell.h"

void    debug(char **splitter, char *changes, t_command_list cmd_lst)
{
    int i = 0;
    int c = 0;
    int j = 0;
    int a = 0;
    if (splitter != NULL)
    {
        printf("\nSplitter Changes\n");
        while (splitter[i])
        printf("String{%d}: %s\n", i, splitter[i++]);
    }
    if (changes != NULL)
    {
        printf("\nChanges changes\n");
        while (changes[j] != '\0')
            printf("Char{%d}: %c", j, changes[j]);
        printf("\n");
    }
    if (cmd_lst != NULL)
    {
        printf("\ncmd_list changes\n");
        while (cmd_lst.arg[a])
            printf("Arg{%d}: %s -->Type: %d\n", a, cmd_lst.arg[a].token, cmd_lst.arg[a++].type);
    }
}