#include "minishell.h"

int sigint_handler(int signal)
{
    system("minishell");
}

int arm_signals()
{
    signal(SIGINT, sigint_handler);
}