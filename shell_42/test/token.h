#ifndef TOKEN_H
#define TOKEN_H

#include "libft/libft.h"
#include "../src/lexer/lexer.h"
#include "../src/tokens/token.h"

struct token
{
    char* value; // se que contien le token ex: "export"
    char* type; // "> << >> < |" , '\n' , ou un mot , commande
    struct token *next; // pointe vers le prochain token (termine par NULL)
};

#endif
