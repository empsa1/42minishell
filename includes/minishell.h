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
#include <sys/stat.h>
#include <fcntl.h>
#include "../libft/libft.h"


typedef struct s_node
{
    char *content;
    struct s_node *next;
}   t_node;

typedef struct s_data
{
    char *name;
    int stdin;
    int stdout;
    int stderr;
    t_node *env;
    t_node *exp;
    char **path;
    char cwd[PATH_MAX];
}   t_data;


typedef enum e_token
{
    ORDINARY,   // str
    IN,         // <
    PIPE,       // |
    LPR,        // (
    RPR,        // )
    SC,         // '
    DC,         // "
    OUT,        // >
    HEREDOC,    // <<
    APPEND,     // >>
    END,        // end of command
}   t_token;

typedef struct s_command
{
    char **cmd;
    char *executable;
    int link;
    int valid;
    struct s_command *next;
}   t_command;

int create_executor(char *command);
void sigint_handler(int signal);
void sigEOF_handler(int signal);
void sigint_handler_parent(int signal);
int exec(char **str);
int	cd(t_data *data, char *str);
int	expand_path(char *str, char *buf);
int	env(t_data *data, char *str);
int export(t_data *data, char *str);
int	unset(t_data *data, char *str);
int pwd(void);
t_data *get_env(char **envp);
void cleanup(t_data *data);
int echo(char *str);

#endif