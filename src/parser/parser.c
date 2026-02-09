/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elquesne <elquesne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 23:07:12 by enzo              #+#    #+#             */
/*   Updated: 2026/02/09 17:17:16 by elquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../tokens/token.h"

static int	droite(struct commandes *cmd, struct token *tmp, int fdfd)
{
	if (strncmp(tmp->value, ">>", 2) == 0 && tmp->next)
	{
		if (cmd->outfile)
		{
			fdfd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fdfd != -1)
				close(fdfd);
			free(cmd->outfile);
		}
		return (cmd->outfile = ft_strdup(tmp->next->value),
			cmd->append_mode = 1, 1);
	}
	else if (strncmp(tmp->value, ">", 1) == 0 && tmp->value[1] == '\0'
		&& tmp->next)
	{
		if (cmd->outfile)
			droite_utils(fdfd, cmd);
		return (cmd->outfile = ft_strdup(tmp->next->value),
			cmd->append_mode = 0, 1);
	}
	else
		return (0);
}

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
	}
}

static int	pars_sub(struct commandes **commande, struct token **token)
{
	struct commandes	*nouvelle;

	nouvelle = ft_calloc(1, sizeof(struct commandes));
	if (!nouvelle)
		return (0);
	(*commande)->next = nouvelle;
	*commande = nouvelle;
	*token = (*token)->next;
	return (1);
}

int	parser(struct token *tokens, struct data *data)
{
	struct commandes	*commande;
	struct token		*token;
	struct token		*tmp;
	struct commandes	*head;

	token = tokens;
	commande = ft_calloc(1, sizeof(*commande));
	if (!commande)
		return (0);
	head = commande;
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
	return (exec(tokens, data, head), free_commande(head), 0);
}
