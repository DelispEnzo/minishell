/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elquesne <elquesne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 17:21:45 by enzo              #+#    #+#             */
/*   Updated: 2026/02/09 17:58:00 by elquesne         ###   ########.fr       */
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

void	enfant_process(t_enfant *enfant)
{
	int		fd_in;
	int		fd_out;
	int		fd_heredoc;
	char	*valid_path;
	int		flag;

	valid_path = NULL;
	les_if(enfant, &fd_heredoc);
	petit_if(enfant, &flag, &fd_out);
	eh_if(enfant, &fd_in);
	if (execution(enfant->commande, enfant->data) == 0
		&& execution_2(enfant->commande, enfant->data) == 0)
	{
		exevv(enfant, valid_path);
		perror("execve");
		exit(126);
	}
	printf("ici\n");
	free_principal(enfant->princ);
	free_machin_truc(enfant->tokens, enfant->data, enfant->cmd);
	free(enfant);
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

void	wh_cmd(t_enfant *enfant, pid_t *pid, int *eh, struct commandes *cmd)
{
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
			enfant_process(enfant);
		}
		else
			el(enfant, eh, cmd, pid);
	}
	
}

int	exec(struct token *tokens, struct data *data, struct commandes *cmd)
{
	t_enfant	*enfant;
	t_principal	*princ;

	princ = malloc(sizeof(t_principal));
	if (!princ)
		return (0);
	princ->commande = cmd;
	enfant = init_enfant_0(princ->commande, tokens, cmd);
	if (!enfant)
		return (free(princ), 0);
	enfant->princ = princ;
	init_enfant_1(enfant, data, princ->fd);
	enfant->commande = cmd;
	wh_cmd(enfant, &princ->pid, &princ->eh, cmd);
	printf("e4\n");
	princ->der_pid = wait(&princ->statue);
	printf("e3\n");
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
	return (0);
}
