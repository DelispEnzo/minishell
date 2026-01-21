#include "token.h"

struct token *get_last_token(struct token* tokens)
{
    struct token *element;

    element = tokens;
    if(!element)
        return(NULL);
    while(element->next != NULL)
    {
        element = element->next;
    }
    return(element);
}

struct token *new_token(struct token* tokens, char *value, char* type)
{
    struct token *next;
    struct token *last_element;

    next = malloc(sizeof(struct token));
    if(!next)
        return(NULL);
    next->value = ft_strdup(value);
    if(!next->value)
    {
        free(next);
        return(NULL);
    }
    next->type = ft_strdup(type);
    if(!next->type)
    {
        free(next->value);
        free(next);
        return(NULL);
    }
    next->next = NULL;
    last_element = get_last_token(tokens);
    if(!last_element)
        return(next);
    last_element->next = next;
    return(tokens);
}

void free_token(struct token* tokens)
{

}

void destroy_tokens(struct token* tokens)
{

}

