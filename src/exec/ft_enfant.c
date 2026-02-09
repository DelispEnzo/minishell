/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enfant.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 11:42:46 by enzo              #+#    #+#             */
/*   Updated: 2026/02/09 14:28:39 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	les_if(t_enfant *enfant, int *fd_heredoc)
{
	if (!enfant->commande->value)
	{
		free_machin_truc(enfant->tokens, enfant->data, enfant->cmd);
		exit(0);
	}
	if (enfant->prev != -1)
	{
		dup2(enfant->prev, STDIN_FILENO);
		close(enfant->prev);
	}
	if (enfant->commande->next)
	{
		close(enfant->fd[0]);
		dup2(enfant->fd[1], STDOUT_FILENO);
		close(enfant->fd[1]);
	}
	if (enfant->commande->heredoc_mode == 1)
	{
		*fd_heredoc = gestion_heredoc(enfant->commande->limiter);
		dup2(*fd_heredoc, STDIN_FILENO);
		close(*fd_heredoc);
	}
}

void	petit_if(t_enfant *enfant, int *flag, int *fd_out)
{
	if (enfant->commande->outfile != NULL)
	{
		if (enfant->commande->append_mode == 1)
			*flag = O_WRONLY | O_CREAT | O_APPEND;
		else
			*flag = O_WRONLY | O_CREAT | O_TRUNC;
		*fd_out = open(enfant->commande->outfile, *flag, 0644);
		if (*fd_out == -1)
		{
			perror(enfant->commande->outfile);
			free_machin_truc(enfant->tokens, enfant->data, enfant->cmd);
			exit(1);
		}
		dup2(*fd_out, STDOUT_FILENO);
		close(*fd_out);
	}
}

void	eh_if(t_enfant *enfant, int *fd_in)
{
	if (enfant->commande->infile != NULL)
	{
		*fd_in = open(enfant->commande->infile, O_RDONLY);
		if (*fd_in == -1)
		{
			perror(enfant->commande->infile);
			free_machin_truc(enfant->tokens, enfant->data, enfant->cmd);
			exit(1);
		}
		dup2(*fd_in, STDIN_FILENO);
		close(*fd_in);
	}
}
