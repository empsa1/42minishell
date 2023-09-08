#include "minishell.h"

void sigint_handler(int signal)
{
    printf("wtf\n");
    if (signal)
        system("minishell");
}

int arm_signals()
{
    //changesgsgseges
    signal(SIGINT, sigint_handler);
    return (0);
}