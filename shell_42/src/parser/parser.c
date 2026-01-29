/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 23:07:12 by enzo              #+#    #+#             */
/*   Updated: 2026/01/29 00:58:45 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/// -------------------------------------------
void print_commands(struct commandes *cmd)
{
    int i;
    int count = 1;

    if (!cmd)
    {
        printf("DEBUG: La liste de commandes est vide (NULL).\n");
        return;
    }

    while (cmd)
    {
        printf("\n========== COMMANDE %d n", count++);

        // 1. Infos de base
        printf("Value (path): %s\n", cmd->value ? cmd->value : "(null)");

        // 2. Affichage de argv (tableau de chaînes)
        printf("Argv:\n");
        if (cmd->argv)
        {
            i = 0;
            while (cmd->argv[i])
            {
                printf("  [%d] : %s\n", i, cmd->argv[i]);
                i++;
            }
        }
        else
        {
            printf("  (null)\n");
        }

        // 3. Redirections
        printf("--- Redirections ---\n");
        printf("Infile       : %s\n", cmd->infile ? cmd->infile : "STDIN (Clavier)");
        printf("Heredoc Mode : %s\n", cmd->heredoc_mode ? "OUI (<<)" : "NON");
        printf("Limiter      : %s\n", cmd->limiter ? cmd->limiter : "(null)");
        printf("Outfile      : %s\n", cmd->outfile ? cmd->outfile : "STDOUT (Ecran)");
        printf("Append Mode  : %s\n", cmd->append_mode ? "OUI (>>)" : "NON (>)");

        // Passage au maillon suivant
        cmd = cmd->next;
    }
    printf("\n=================================\n");
}
//--------------------------------------------------------------

int size_argv(struct token *token)
{
	int i;

	i = 0;
	while (token != NULL && strncmp(token->type, "pipe", 5) != 0)
	{
		token = token->next;
		i++;
	}
	return (i);
}

struct token *avance_token(struct token *token, int i)
{
	int x;
	struct token *tmp;
	tmp = token;
	x = 0;
	while (x < i && tmp != NULL)
	{
		tmp = tmp->next;
		x++;
	}
	return (tmp);
}

void cpy_commande(struct token *token, struct commandes *cmd)
{
	int i;

	i = 0;
	struct token *tmp;

	tmp = token;
	while (tmp != NULL && strncmp(tmp->type, "pipe", 5) != 0)
	{
		if (strncmp(tmp->value, "<", 1) == 0 && tmp->value[1] == '\0' && tmp->next)
        {
            cmd->infile = ft_strdup(tmp->next->value);
            cmd->heredoc_mode = 0;
            tmp = tmp->next; // On saute le fichier
        }
        // 2. Gestion HEREDOC '<<'
        // On compare value avec "<<" (taille 2)
        else if (strncmp(tmp->value, "<<", 2) == 0 && tmp->next)
        {
            cmd->limiter = ft_strdup(tmp->next->value);
            cmd->heredoc_mode = 1;
            tmp = tmp->next; // On saute le limiteur
        }
        // 3. Gestion APPEND '>>' (Ajout)
        // ATTENTION : Il faut tester '>>' AVANT '>' sinon '>' matchera le début de '>>'
        else if (strncmp(tmp->value, ">>", 2) == 0 && tmp->next)
        {
            cmd->outfile = ft_strdup(tmp->next->value);
            cmd->append_mode = 1;
            tmp = tmp->next; // On saute le fichier
        }
        // 4. Gestion TRUNCATE '>' (Écrasement)
        else if (strncmp(tmp->value, ">", 1) == 0 && tmp->value[1] == '\0' && tmp->next)
        {
            cmd->outfile = ft_strdup(tmp->next->value);
            cmd->append_mode = 0;
            tmp = tmp->next; // On saute le fichier
        }
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

int parser(struct token *token, struct data *data)
{
	struct commandes *commande;
	struct token *tmp;
	struct commandes *head;

	head = NULL;
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
		token = avance_token(token, size_argv(token));
		cpy_commande(tmp, commande);

		if (token != NULL && strncmp(token->type, "pipe", 5) == 0)
		{
			struct commandes *nouvelle;
			nouvelle = ft_calloc(1, sizeof(struct commandes));
			token = token->next;
			commande->next = nouvelle;
			commande = commande->next;
		}
		else
			break;
	}
	exec(token, data, head);
	return (0);
}
