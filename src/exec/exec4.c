/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 13:24:53 by enzo              #+#    #+#             */
/*   Updated: 2026/02/11 13:24:58 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	init_enfant_1(t_enfant *enfant, struct data *data, int *fd)
{
	int	prev;

	prev = -1;
	enfant->data = data;
	enfant->fd = fd;
	enfant->prev = prev;
}

void	no_valid_path(t_enfant *enfant, t_all *all, char *valid_path)
{
	if (execution(enfant->commande, enfant->data) == 0
		&& execution_2(enfant->commande, enfant->data) == 0)
	{
		exevv(enfant, valid_path, all);
		perror("execve");
		free_machin_truc(enfant->tokens, enfant->data, enfant->cmd);
		free(enfant);
		DIXDOUZEQUATORZBUREAUX(all);
		exit(126);
	}
}
