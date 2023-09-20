#include "minishell.h"

int zcmp(char *str, char *cmp)
{
    int i;

    i = 0;
    while (str[i] != '\0' && cmp[i] != '\0')
    {
        if (str[i] != cmp[i])
            return 0;
        i++;
    }
    if (str[i] != '\0' || cmp[i] != '\0')
        return 0;
    return 1;
}