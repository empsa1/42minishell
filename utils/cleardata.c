#include "minishell.h"

//clears previous cmd_lst linked nodes
void    free_linkedlst(t_command_list *cmd_lst)
{
    t_command_list *to_clean;

    to_clean = cmd_lst;
    while (cmd_lst->next != NULL)
        to_clean = to_clean->next;
    free(to_clean);
    free_linkedlst(cmd_lst);
}

void    free_all(t_command_list *cmd_lst, char *line, char *changes, char **splitter)
{
    free_linkedlst(cmd_lst);
    free(changes);
    free(splitter);
    free(line);
}