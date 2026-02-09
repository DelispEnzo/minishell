/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elquesne <elquesne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 17:23:27 by enzo              #+#    #+#             */
/*   Updated: 2026/02/09 17:51:23 by elquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exevv(t_enfant *enfant, char *valid_path)
{
	int	k;

	k = 0;
	printf("e1\n");
	char buf;
	read(1, &buf, 0);
	valid_path = check_path(enfant->commande->value, enfant->data);
	if (valid_path == NULL)
	{
		free(valid_path);
		if (enfant->princ)
			free_principal(enfant->princ);
		valid_null(enfant->commande, valid_path);
		free_machin_truc(enfant->tokens, enfant->data, enfant->cmd);
		free(enfant);
		//exit(127);
		printf("32\n");
		return;
	}
	k = execve(valid_path, enfant->commande->argv, enfant->data->env);
	if (k < 0)
	{
		free(valid_path);
		exit(127);
	}
	free(valid_path);
}

t_enfant	*init_enfant_0(struct commandes *commande, struct token *tokens,
		struct commandes *cmd)
{
	t_enfant	*enfant;

	enfant = malloc(sizeof(t_enfant));
	if (!enfant)
		return (NULL);
	enfant->commande = commande;
	enfant->tokens = tokens;
	enfant->cmd = cmd;
	return (enfant);
}

void	valid_null(struct commandes *commande, char *valid_path)
{
	write(2, "minishell: command not found: ", 30);
	write(2, commande->value, ft_strlen(commande->value));
	write(2, "\n", 1);
	free(valid_path);
}
