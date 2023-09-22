#include "includes/minishell.h"

void terminal_prompt()
{
    rl_reset_line_state();
    rl_cleanup_after_signal();
    rl_replace_line("", 0);
    rl_crlf();
    rl_redisplay();

}

void sigint_handler(int signal)
{
    if (signal)
    {
        kill(getpid(), SIGSEGV); //Função proibida
        terminal_prompt();
    }
}