#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include "libft/libft.h"
#include "../src/lexer/lexer.h"
#include <stdio.h>
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

struct data
{
    char **result_split; //resultat de slpit de readline
    char **env; //copie de l'environement
    char **path_split; //chemin du path
};

struct token *new_token(struct token* tokens, char *value, char* type); //crée un nouveau token
void free_token(struct token* tokens); // detruit un token
void destroy_tokens(struct token* tokens); // detruit tout les token

#endif
