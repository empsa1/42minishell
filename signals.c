#include "minishell.h"

void sigint_handler(int signal)
{
    printf("Received SIGINT signal\n");
    if (signal)
    {
        printf("Killed child process %d \n", getpid());
        exit(0); //Killing child process
    }
}

void sigint_handler_parent(int signal)
{
    printf("Received SIGINT signal\n");
    if (signal)
    {
        create_executor(NULL);
        printf("Killed child process %d \n", getpid());
    }
}

// void sigEOF_handler(int signal)
// {
//     printf("PIcked up a Ctrl + D signal\n");
//     if (signal)
//     {
//         rl_clear_history();
//         exit(0); //Killing parent process
//     }
// }