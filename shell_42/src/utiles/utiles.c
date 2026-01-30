/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelispo <edelispo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:22:04 by elquesne          #+#    #+#             */
/*   Updated: 2026/01/30 19:31:04 by edelispo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"utiles.h"

void free_tab(char** tab)
{
	int i;

	i = 0;
	if (!tab)
		return;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return;
}

int ft_tab_len(char** tab) // Donne la taillle d'un tableau de tableau
{
	int i;

	i = 0;
	if (!tab)
		return (1);
	while (tab[i])
	{
		i++;
	}
	return(i);
}

void free_all(char *line, struct data *data, struct token *tokens, char **arg) // OK
{
	int i;

	i = 0;
	free(line);
	if (data->env)
	{
		while (data->env[i])
		{
			free(data->env[i]);
			i++;
		}
		free(data->env);
	}
	i = 0;
	if (data->path_split)
	{
		while (data->path_split[i])
		{
			free(data->path_split[i]);
			i++;
		}
		free(data->path_split);
	}
	i = 0;
	if (data->result_split)
	{
		while (data->result_split[i])
		{
			free(data->result_split[i]);
			i++;
		}
		free(data->result_split);
	}
	i = 0;
	if (arg)
	{
		while (arg[i])
		{
			free(arg[i]);
			i++;
		}
		free(arg);
	}
	destroy_tokens(tokens);
	free(data);
	clear_history();
}
