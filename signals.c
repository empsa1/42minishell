#include "minishell.h"

int sigint_handler(int signal)
{
    system("minishell");
    return (signal);
}

int arm_signals()
{
    signal(SIGINT, &sigint_handler);
}