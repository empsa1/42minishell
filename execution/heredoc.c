int mini_heredoc(char *line)
{
    char *heredoc = "";
    if (!ft_strncmp(line, "<<", 2))
    {
        while (strncmp(heredoc, "EOF", 3))
            heredoc = readline("heredoc>");
    }
}