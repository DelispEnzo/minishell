#ifndef TOKEN_H
#define TOKEN_H

#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

struct token
{
    char* value; // se que contien le token ex: "export"
    char* type; // "> << >> < |" , '\n' , ou un mot , commande
    struct token *next; // pointe vers le prochain token (termine par NULL)
};

// void free_token(struct token* tokens); // detruit un token
void destroy_tokens(struct token* tokens); // detruit tout les token
struct token *new_token(struct token* tokens, char *value, char* type); //cree le nouveau token

#endif
