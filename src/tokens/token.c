/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2026/02/06 18:20:15 by enzo              #+#    #+#             */
/*   Updated: 2026/02/06 18:20:15 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

struct token	*get_last_token(struct token *tokens)
{
	struct token	*element;

	element = tokens;
	if (!element)
		return (NULL);
	while (element->next != NULL)
	{
		element = element->next;
	}
	return (element);
}

struct token	*mall_tok(struct token *next, char *value)
{
	next = malloc(sizeof(struct token));
	if (!next)
		return (NULL);
	next->value = ft_strdup(value);
	return (next);
}

struct token	*new_token(struct token *tokens, char *value, char *type)
{
	struct token	*next;
	struct token	*last_element;

	next = NULL;
	next = mall_tok(next, value);
	if (!next || !next->value)
	{
		free(next);
		return (NULL);
	}
	next->type = ft_strdup(type);
	if (!next->type)
	{
		free(next->value);
		free(next);
		return (NULL);
	}
	next->next = NULL;
	last_element = get_last_token(tokens);
	if (!last_element)
		return (next);
	return (last_element->next = next, tokens);
}

void	destroy_tokens(struct token *tokens) // ok
{
	struct token	*current;
	struct token	*temp;

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
