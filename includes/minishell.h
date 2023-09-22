#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

enum						tokens
{
	STR,     // str
	IN,      // <
	OUT,     // >
	APPEND,  // >>
	HEREDOC, // <<
	PIPE,    // |
	END,     // ; (end of command)
};

typedef struct s_node
{
	char					*content;
	struct s_node			*next;
}							t_node;

typedef struct s_pair
{
	char					*key;
	char					*value;
	struct s_pair			*next;
}							t_pair;

typedef struct s_pipe
{
	int						fd[2];
	int						open;
	struct s_pipe			*next;
}							t_pipe;

typedef struct s_data
{
	char					*name;
	int						heredoc;
	int						exit_status;
	t_pair					*env;
	t_pair					*exported_vars;
	char					**path;
	struct s_pipe			pipes;
	char					cwd[PATH_MAX];
}							t_data;

typedef struct s_arg
{
	char					*token;
	int						type;
}							t_arg;

typedef struct s_command_list
{
	char					*exec_path;
	t_arg					*arg;
	int						stdin;
	int						stdout;
	int						in_fd;
	int						out_fd;
	struct s_command_list	*next;
}							t_command_list;

void						print_struct(t_command_list *lst);
int							ft_strleni(char **splitter, int i);
int							z_cmp(char *str, char *cmp);
void						free_all(t_command_list *cmd_lst, char *line,
								char *changes, char **splitter);
void						parsing(t_command_list *cmd_lst, char **splitter,
								int i);
int							create_executor(char *command);
void						sigint_handler(int signal);
int							exec(char **str);
int							cd(t_data *data, char *str);
int							expand_path(char *str, char *buf);
int							env(t_pair *env, t_pair *exported_vars, char *str);
int							export(t_pair *env, t_pair *exported_vars,
								char **str);
int							unset(t_data *data, char **str);
int							pwd(void);
t_pair						*get_env(char **envp);
void						cleanup(t_data *data);
int							echo(char *str);
int							get_length_to_char(char *str, char c);
void						free_nodes(t_node *node);
void						print_nodes(t_node *node);
void						print_pairs(t_pair *pair);
void						print_exported(t_node *node);
void						free_pairs(t_pair *pair);
void						sort_list(t_pair *export);
int							print_syntax_error(char c);
int							print_file_error(char *s1, char *s2);
int							token_error(char *str);
int							check_unclosed(char *str);
void						terminal_prompt(void);
void						sigint_handler(int signal);
int							print_parse_error(char c);
char						*treat_str(char *line);
int							mini_heredoc(t_data *data, char *str);
int							check_cmd(t_data *data, t_command_list *cmd_lst,
								t_pipe *pipes);
t_pair						*get_env(char **envp);
char						*get_next_line(int fd);
int							token_error(char *str);
char						**get_arg_list(t_arg *arg);
int							open_file(int *fd, char *filename, int flags,
								int perms);
void						revert_fds(t_command_list *cmd_lst);
int							check_path(char **path, t_command_list *cmd_lst);

#endif