/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 17:23:27 by enzo              #+#    #+#             */
/*   Updated: 2026/02/11 13:25:24 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exevv(t_enfant *enfant, char *valid_path, t_all *all)
{
	int		k;
	char	buf;

	k = 0;
	read(1, &buf, 0);
	valid_path = check_path(enfant->commande->value, enfant->data);
	if (valid_path == NULL)
	{
		free_principal(enfant->princ);
		valid_null(enfant->commande, valid_path);
		free_machin_truc(enfant->tokens, enfant->data, enfant->cmd);
		free(enfant);
		DIXDOUZEQUATORZBUREAUX(all);
		exit(127);
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
