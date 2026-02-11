/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 17:48:21 by enzo              #+#    #+#             */
/*   Updated: 2026/02/11 13:16:56 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	execution(struct commandes *cmd, struct data *data)
{
	int	i;

	i = 0;
	if (!cmd->value)
		return (0);
	else if (ft_strcmp(cmd->value, "pwd") == 0)
	{
		i = ft_pwd();
		data->return_code = 0;
		return (1);
	}
	else if (ft_strcmp(cmd->value, "env") == 0)
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
	if (ft_strcmp(cmd->value, "cd") == 0)
	{
		ft_cd(cmd->argv, data);
		return (1);
	}
	else if (ft_strcmp(cmd->value, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd->value, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd->value, "echo") == 0)
	{
		data->return_code = 0;
		echo(cmd->argv);
		return (1);
	}
	return (0);
}

void	free_machin_truc_2(struct data *data)
{
	if (data->path_split)
	{
		free_tab(data->path_split);
		data->path_split = NULL;
	}
	if (data->export_tab)
	{
		free_tab(data->export_tab);
		data->export_tab = NULL;
	}
	if (data->env)
	{
		free_tab(data->env);
		data->env = NULL;
	}
}

void	free_machin_truc(struct token *tokens, struct data *data,
		struct commandes *cmd)
{
	if (cmd)
	{
		free_commande(cmd);
		cmd = NULL;
	}
	if (tokens)
	{
		destroy_tokens(tokens);
		tokens = NULL;
	}
	if (data)
	{
		if (data->result_split)
		{
			free_tab(data->result_split);
			data->result_split = NULL;
		}
		free_machin_truc_2(data);
		free(data);
		data = NULL;
	}
}

void	commande_parent(struct commandes *cmd, struct data *data, int prev)
{
	if (!cmd || !cmd->value)
	{
		if (prev != -1)
			close(prev);
		return ;
	}
	if (ft_strcmp(cmd->value, "cd") == 0)
	{
		ft_cd(cmd->argv, data);
	}
	else if (ft_strcmp(cmd->value, "unset") == 0)
	{
		ft_unset(cmd->argv, data);
	}
	else if (ft_strcmp(cmd->value, "export") == 0)
	{
		ft_export(cmd->argv, data);
	}
	if (prev != -1)
		close(prev);
}
