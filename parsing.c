#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


enum tokens
{
    STR,   // str
    IN,         // <
    OUT,        // >
    APPEND,     // >>
    HEREDOC,    // <<
    PIPE,       // |
    END,        // ; (end of command)
};

typedef struct s_arg
{
    char    *token;
    int     type;
    struct s_arg *next;
}   t_arg;


typedef struct s_command_list
{
    char *exec_name;
    char *exec_path;
    struct s_arg *arg;
    int stdin;
    int stdout;
    int in_fd;
    int out_fd;
    struct s_command_list *next;
}   t_command_list;


size_t	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
    printf("Ft_strlen result: %d\n", i);
	return (i);
}

//iterates spaces until it reaches something
int kill_spaces(char *string, int index)
{
    printf("INside kill_spaces()\n");
    if (*string)
    {
        while (string[index] == ' ')
        index++;
    }
    printf("index where spaces end: %d\n", index);
    return (index);
}

//loop through files to check if command exists in the machine
int is_valid_command(t_command_list to_exec)
{
    return 0;
}

void    iterate(char *line)
{
    int i;
    i = 0;
    printf("Iterating: {%s}\n", line);
    while (*line)
    {
        printf("[%d]: %c\n", i, *line);
        i++;
        line++;
    }
}

void    init_cmdlst(t_command_list **cmd_lst)
{
    *cmd_lst = malloc(sizeof(t_command_list));
}

void    init_cmdlst_atr(char *string, char*line, int index)
{
    int len;
    while (line[index] != ' ')
    {
        len++;
        index++;
    }
    string = malloc(sizeof(char) * len);
}

void    init_arg(t_arg arg, char *line, int index)
{
    int len;

    len = 0;
    while (line[index] != ' ')
    {
        len++;
        index++;
    }
    arg = malloc(sizeof(arg));
    arg.token = malloc(sizeof(char) * len);
}

void parsing(t_command_list **cmd_lst, char *line)
{
    printf("Entered parsing()\n");
    int i;
    int c;
    int j;

    i = 0;
    c = 0;
    j = 0;
    iterate(line);
    init_cmdlst(&cmd_lst);
    printf("initialized first cmdlist\n");
    while (line[i] != '\0')
    {
        i = kill_spaces(line, i);
        init_cmdlst_atr(&cmd_lst.exec_name, line, i);
        while (line[i] != ' ')
            cmd_lst.exec_name[j++] = line[i++];
        if (!is_valid_command(&cmd_lst))
            ft_putstr_fd();
        i = kill_spaces(line, i);
        break;
    }
    catch_args(&cmd_lst[c], line, i);
}

void    assign_type(t_arg arg)
{
    if (ft_strcmp(arg.token, '<'))
        arg.type = IN;
    else if (ft_strcmp(arg.token, '>'))
        arg.type = OUT;
    else if (ft_strcmp(arg.token, '>>'))
        arg.type = APPEND;
    else if (ft_strcmp(arg.token, '<<'))
        arg.type == HEREDOC;
    else if (ft_strcmp(arg.token, '|'))
        arg.type = PIPE;
    else if (ft_strcmp(arg.token, ';'))
        arg.type = END;
    else
        arg.type = STR;
}

int   catch_args(t_command_list *cmd_list, char* line, int index)
{
    int c;
    int i;

    i = 0;
    c = 0;
    while (line[index] != '\0' && line[index] != '|' \
            && line[index] != ';')
    {
        init_arg(&cmd_list->arg[c], line, index);
        while (line[index] != ' ')
        {
            *cmd_list->arg[c][i] = line[index];
            i++;
            index++;
        }
        assign_type(*cmd_list->arg[c]);
        c++;
    }
    // if (line[index] == '|' && line[index] == ';')
    // {
    //     init_cmdlst();
    //     cmd_list->next = cmd_list[++c];
    //     //parsing();
    // }
}

echo2"ls -as"2|2e '2' 2

int main(int argc, char**argv)
{
    t_command_list *cmd_list;
    char* commands;
    //printf("GOing to append_all()\n");
    //commands = append_all(argv);
    cmd_list = NULL;
    commands = argv[1];
    printf("Index where flags die: %d\n", parsing(&cmd_list, argv[1]));
}