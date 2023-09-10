#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include <linux/limits.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../libft/libft.h"


typedef struct s_env
{
    char *content;
    struct s_env *next;
}   t_env;

typedef struct s_data
{
    char *name;
    int stdin;
    int stdout;
    int stderr;
    t_env *env;
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
    char **cmd;
    char *executable;
    struct s_command *next;
    int link;
}   t_command;

int	print_error(char *msg);
int arm_signals();
int exec(char **str);
int	cd(t_data *data, char *str);
int	expand_path(char *str, char *buf);

#endif