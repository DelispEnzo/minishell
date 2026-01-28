#include "exec.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>

int gestion_heredoc(char *delimiteur)
{
    int     fd;
    char    *ligne;

    fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0)
        return (-1);
    while (1)
    {
        ligne = readline("> ");
        if (!ligne)
            break;
        if (strcmp(ligne, delimiteur) == 0)
        {
            free(ligne);
            break;
        }
        write(fd, ligne, strlen(ligne));
        write(fd, "\n", 1);
        free(ligne);
    }
    close(fd);
    fd = open(".heredoc_tmp", O_RDONLY);
    unlink(".heredoc_tmp");
    return (fd);
}
