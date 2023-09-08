#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include <linux/limits.h>
#include "../libft/libft.h"



typedef struct s_data
{
    char *name;
    int stdin;
    int stdout;
    int stderr;
    char **path;
    char cwd[PATH_MAX];
}   t_data;

typedef enum e_token
{
    PIPE,       // |
    HEREDOC,    // <<
    LPR,        // (
    RPR,        // )
    SC,         // '
    DC,         // "
    OUT,        // >
    IN,         // <
    APPEND,     // >>
    END,        // end of command
}   t_token;

typedef struct s_command
{
    char *cmd;
    struct s_command *next;
    int link;
}   t_command;

int	print_error(char *msg);
void check_line(char *line);
int arm_signals();
int exec(char **str);
void test();

#endif