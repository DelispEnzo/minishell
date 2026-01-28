#ifndef UTILES_H
#define UTILES_H

#include "../libft/libft.h"
#include "../tokens/token.h"
#include "../lexer/lexer.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

struct data;
struct token;

void free_tab(char** tab);
int ft_tab_len(char** tab);
void free_all(char *line, struct data *data, struct token *tokens, char **arg);

#endif
