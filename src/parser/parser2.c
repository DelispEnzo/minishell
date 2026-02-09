/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:07:37 by enzo              #+#    #+#             */
/*   Updated: 2026/02/09 14:30:01 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	droite_utils(int fdfd, struct commandes *cmd)
{
	fdfd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdfd != -1)
		close(fdfd);
	free(cmd->outfile);
}

int	size_argv(struct token *token)
{
	int	i;

	i = 0;
	while (token != NULL && strncmp(token->type, "pipe", 5) != 0)
	{
		token = token->next;
		i++;
	}
	return (i);
}

struct token	*avance_token(struct token *token, int i)
{
	int				x;
	struct token	*tmp;

	tmp = token;
	x = 0;
	while (x < i && tmp != NULL)
	{
		tmp = tmp->next;
		x++;
	}
	return (tmp);
}

int	gauche(struct commandes *cmd, struct token *tmp)
{
	if (strncmp(tmp->value, "<", 1) == 0 && tmp->value[1] == '\0' && tmp->next)
	{
		cmd->infile = ft_strdup(tmp->next->value);
		cmd->heredoc_mode = 0;
	}
	else if (strncmp(tmp->value, "<<", 2) == 0 && tmp->next)
	{
		cmd->limiter = ft_strdup(tmp->next->value);
		cmd->heredoc_mode = 1;
	}
	else
		return (0);
	return (1);
}
