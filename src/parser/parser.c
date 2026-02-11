/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 23:07:12 by enzo              #+#    #+#             */
/*   Updated: 2026/02/11 13:29:53 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokens/token.h"
#include "parser.h"

void	cpy_commande(struct token *token, struct commandes *cmd)
{
	int				i;
	struct token	*tmp;
	int				fdfd;

	i = 0;
	fdfd = 0;
	tmp = token;
	while (tmp != NULL && strncmp(tmp->type, "pipe", 5) != 0)
	{
		if (gauche(cmd, tmp) == 1)
			tmp = tmp->next;
		else if (droite(cmd, tmp, fdfd) == 1)
			tmp = tmp->next;
		else
		{
			if (i == 0)
				cmd->value = strdup(tmp->value);
			cmd->argv[i] = strdup(tmp->value);
			i++;
		}
		tmp = tmp->next;
	}
	cmd->argv[i] = NULL;
}

void	free_commande(struct commandes *cmd)
{
	struct commandes	*tmp;

	if (!cmd)
		return ;
	tmp = cmd;
	while (cmd != NULL)
	{
		if (cmd->argv)
			free_tab(cmd->argv);
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->limiter)
			free(cmd->limiter);
		if (cmd->outfile)
			free(cmd->outfile);
		if (cmd->value)
			free(cmd->value);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
		tmp = NULL;
	}
}

static int	pars_sub(struct commandes **commande, struct token **token)
{
	struct commandes	*nouvelle;

	nouvelle = ft_calloc(1, sizeof(struct commandes));
	if (!nouvelle)
		return (0);
	nouvelle->heredoc_fd = -1;
	nouvelle->heredoc_expand = 1;
	(*commande)->next = nouvelle;
	*commande = nouvelle;
	*token = (*token)->next;
	return (1);
}

void	init_heardoc(struct commandes *commande, struct commandes **head)
{
	commande->heredoc_fd = -1;
	commande->heredoc_expand = 1;
	*head = commande;
}

int	parser(t_all *all)
{
	struct commandes	*commande;
	struct token		*token;
	struct token		*tmp;
	struct commandes	*head;

	token = all->tokens;
	commande = ft_calloc(1, sizeof(*commande));
	if (!commande)
		return (0);
	init_heardoc(commande, &head);
	while (token != NULL)
	{
		commande->argv = malloc(sizeof(char *) * (size_argv(token) + 1));
		if (!commande->argv)
			return (0);
		tmp = token;
		commande->argv[size_argv(token)] = NULL;
		token = avance_token(token, size_argv(token));
		cpy_commande(tmp, commande);
		if (token != NULL && strncmp(token->type, "pipe", 5) == 0)
			pars_sub(&commande, &token);
		else
			break ;
	}
	return (exec(all, head), free_commande(head), 0);
}
