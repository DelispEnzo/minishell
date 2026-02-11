/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 17:21:45 by enzo              #+#    #+#             */
/*   Updated: 2026/02/11 13:21:46 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	enfant_process(t_enfant *enfant, t_all *all)
{
	int		fd_in;
	int		fd_out;
	int		fd_heredoc;
	char	*valid_path;
	int		flag;

	if (strcmp(enfant->commande->argv[0], "./minishell") == 0)
	{
		signal(SIGINT, 0); // a verifier
		signal(SIGQUIT, 0);
	}
	valid_path = NULL;
	les_if(enfant, &fd_heredoc);
	petit_if(enfant, &flag, &fd_out);
	eh_if(enfant, &fd_in);
	no_valid_path(enfant, all, valid_path);
	if (enfant->princ)
		free_principal(enfant->princ);
	free_machin_truc(enfant->tokens, enfant->data, enfant->cmd);
	free(enfant);
	DIXDOUZEQUATORZBUREAUX(all);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	exit(0);
}

void	el(t_enfant *enfant, int *eh, struct commandes *cmd, pid_t *pid)
{
	if (!enfant->commande->next)
		*eh = *pid;
	commande_parent(cmd, enfant->data, enfant->prev);
	if (enfant->commande->next)
	{
		close(enfant->fd[1]);
		enfant->prev = enfant->fd[0];
	}
	enfant->commande = enfant->commande->next;
}

void	wh_cmd(t_enfant *enfant, t_principal	*princ, struct commandes *cmd,
		t_all *all)
{
	int		*eh;
	pid_t	*pid;

	eh = &princ->eh;
	pid = &princ->pid;
	while (enfant->commande)
	{
		if (enfant->commande->next)
		{
			if (pipe(enfant->fd) == -1)
				exit(1);
		}
		*pid = fork();
		if (*pid == 0)
		{
			enfant_process(enfant, all);
		}
		else
			el(enfant, eh, cmd, pid);
	}
}

void	wait_enfant_exit(t_principal *princ, t_enfant *enfant)
{
	while (princ->der_pid > 0)
	{
		if (princ->der_pid == princ->eh)
		{
			if (WIFEXITED(princ->statue))
				enfant->data->return_code = WEXITSTATUS(princ->statue);
			else if (WIFSIGNALED(princ->statue))
				enfant->data->return_code = 128 + WTERMSIG(princ->statue);
		}
		princ->der_pid = wait(&princ->statue);
	}
	free_principal(princ);
	free(enfant);
}

int	exec(t_all *all, struct commandes *cmd)
{
	t_enfant	*enfant;
	t_principal	*princ;

	if (cmd->value && ft_strcmp(cmd->value, "./minishell"))
	{
		signal(SIGINT, NULL);
	}
	princ = malloc(sizeof(t_principal));
	if (!princ)
		return (0);
	princ->commande = cmd;
	enfant = init_enfant_0(princ->commande, all->tokens, cmd);
	if (!enfant)
		return (free(princ), 0);
	enfant->princ = princ;
	init_enfant_1(enfant, all->data, princ->fd);
	enfant->commande = cmd;
	wh_cmd(enfant, princ, cmd, all);
	princ->der_pid = wait(&princ->statue);
	wait_enfant_exit(princ, enfant);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
