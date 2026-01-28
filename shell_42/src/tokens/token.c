/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:21:17 by enzo              #+#    #+#             */
/*   Updated: 2026/01/23 16:21:17 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

struct token *get_last_token(struct token* tokens) //recupere le dernier token
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

struct token *new_token(struct token* tokens, char *value, char* type) //cree le nouveau token
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

void destroy_tokens(struct token* tokens) // ok
{
	struct token *current;
	struct token *temp;

	current = tokens;
	while (current != NULL)
	{
		temp = current->next;
		free(current->value);
		free(current->type);
		free(current);
		current = temp;
	}
}
