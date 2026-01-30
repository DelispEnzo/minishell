#ifndef BUILT_IN_H
#define BUILT_IN_H

#include "../lexer/lexer.h"
#include "../libft/libft.h"
#include "../tokens/token.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

struct token;
struct data;
struct commandes;

int env(struct data *data);
int echo(char **argv);
int ft_pwd(void);
int ft_exit(struct token *tokens);
int ft_export(struct token *tk, struct data *dt);
void ft_cd(char** args, struct data* data);

#endif
