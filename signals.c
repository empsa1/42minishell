#include "minishell.h"

void sigint_handler(int signal)
{
    if (signal)
        exit(0);
}

int arm_signals()
{
    //fsdafasdasffa
    //changesgsgseges
    signal(SIGINT, sigint_handler);
    return (0);
}