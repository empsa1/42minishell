#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_command
{
    char **cmd;
    char *executable;
    int link;
    int valid;
    struct s_command *next;
}   t_command;


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
int is_valid_command(t_command to_exec)
{
    
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

int create_reader()
{
    
}

int solve_rest()
{
    
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	strlen;
	char	*substr;

	i = 0;
	strlen = ft_strlen(s);
	if (start >= strlen)
		len = 0;
	else if (strlen - start < len)
		len = strlen - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	while (len--)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}

int size_all(char **args)
{
    int i;
    int c;
    int total_size;

    i = 1;
    c = 0;
    total_size = 0;
    if (!args[i])
        return (total_size);
        while (args[i])
    {
        while (args[i][c++] != '\0')
            total_size++;
        total_size++;
        c = 0;
        i++;
    }
    return (total_size);
}

char    *append_all(char **args)
{
    int i;
    int c;
    int j;
    char* commands;
    int total_size;

    i = 1;
    c = 0;
    j = 0;
    total_size = size_all(args);
    commands = malloc(sizeof(char) * total_size);
    printf("DOne commands malloc\n");
    while (args[i])
    {
        while (args[i][c] != '\0')
        {
            printf("Inside core conditon\n");
            commands[j] = args[i][c];
            j++;
            c++;
        }
        commands[j] = ' ';
        j++;
        c = 0;
        i++;
    }
    printf("Command single string after append_all(): %s\n", commands);
    return (commands);
}

t_command *parsing(char *line)
{
    int i;
    int j;
    int temp;
    t_command *to_exec;

    j = 0;
    i = 0;
    temp = 0;
    to_exec = malloc(sizeof(t_command) * 10);
    to_exec[j].valid = 0;
    while (line[i] != '\0')
    {
        temp = kill_spaces(line, i);
        if (temp != i)
            to_exec[j].cmd[0] = ft_substr(line, temp, i);
        if (!is_valid_command(to_exec[j]))
            return (NULL);
        i = solve_rest(to_exec[j], line, catch_flags(to_exec[j],line, 
            kill_spaces(line, i)));
        if (line[i] == '|')
            to_exec[j].next = &(to_exec[++j]);
        i++;
    }
    return (to_exec);
}

int   catch_flags(t_command to_exec, char* line, int index)
{
    int i;

    i = 0;
    to_exec.cmd = malloc(sizeof(char*) * 100);
    to_exec.cmd[1] = malloc(sizeof(char) * ft_strlen(line));
    to_exec.cmd[1][i++] = '-';
    iterate(line);
    while (line[index] != '\0')
    {
        if (line[index] == '-')
        {
            index++;
            to_exec.cmd[1][i] = line[index];
            i++;
            index++;
            index = kill_spaces(line, index);
        }
        else
        {
            printf("Last Flag: %c\n", line[index]);
            printf("Flags: %s\n", to_exec.cmd[1]);
            return --index;
        }
    }
    printf("Last Flag: %c\n", line[index]);
    printf("Flags: %s\n", to_exec.cmd[1]);
    return (--index);
}

int main(int argc, char**argv)
{
    t_command *to_exec;
    to_exec = malloc(sizeof(t_command) * 100);
    char* commands;
    //printf("GOing to append_all()\n");
    //commands = append_all(argv);
    commands = argv[1];
    printf("Index where flags die: %d\n", catch_flags(*to_exec, argv[1], 3));
}