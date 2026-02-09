/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elquesne <elquesne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 17:48:21 by enzo              #+#    #+#             */
/*   Updated: 2026/02/09 16:32:50 by elquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	execution(struct commandes *cmd, struct data *data)
{
	int	i;

	i = 0;
	if (!cmd->value)
		return (0);
	else if (strcmp(cmd->value, "pwd") == 0)
	{
		i = ft_pwd();
		data->return_code = 0;
		return (1);
	}
	else if (strcmp(cmd->value, "env") == 0)
	{
		i = env(data);
		data->return_code = 0;
		return (1);
	}
	return ((void)i, 0);
}

int	execution_2(struct commandes *cmd, struct data *data)
{
	if (!cmd->value)
		return (0);
	if (strcmp(cmd->value, "cd") == 0)
	{
		ft_cd(cmd->argv, data);//////// ft_strcmp
		return (1);
	}
	else if (strcmp(cmd->value, "export") == 0)
		return (1);
	else if (strcmp(cmd->value, "unset") == 0)
		return (1);
	else if (strcmp(cmd->value, "echo") == 0)
	{
		data->return_code = 0;
		echo(cmd->argv);
		return (1);
	}
	return (0);
}

void	free_machin_truc(struct token *tokens, struct data *data,
		struct commandes *cmd)
{
	if (cmd)
		free_commande(cmd);
	if (tokens)
		destroy_tokens(tokens);
	if (data)
	{
		if (data->result_split)
			free_tab(data->result_split);
		if (data->path_split)
			free_tab(data->path_split);
		if (data->export_tab)
			free_tab(data->export_tab);
		if (data->env)
			free_tab(data->env);
		free(data);
	}
}

void	commande_parent(struct commandes *cmd, struct data *data, int prev)
{
	if (strcmp(cmd->value, "cd") == 0)
	{
		ft_cd(cmd->argv, data);
	}
	else if (strcmp(cmd->value, "unset") == 0)
	{
		ft_unset(cmd->argv, data);
	}
	else if (strcmp(cmd->value, "export") == 0)
	{
		ft_export(cmd->argv, data);
	}
	if (prev != -1)
		close(prev);
}
