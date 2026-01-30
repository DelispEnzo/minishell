#ifndef EXEC_H
# define EXEC_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../tokens/token.h"
#include "../lexer/lexer.h"
#include <fcntl.h>
#include <readline/readline.h>
#include "../parser/parser.h"

struct token;
struct data;
struct commandes;

// --- PROTOTYPES ---
int	execution(struct commandes *cmd, struct token *tokens, struct data *data);
int	exec(struct token *tokens, struct data *data, struct commandes *cmd);
int gestion_heredoc(char *delimiteur);

#endif
