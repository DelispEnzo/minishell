/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:30:03 by enzo              #+#    #+#             */
/*   Updated: 2026/02/09 14:26:22 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	utils_cpy_env(char **env, struct data *data)
{
	int	i;
	int	x;

	i = 0;
	while (env[i])
	{
		x = 0;
		data->env[i] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		if (!data->env[i])
		{
			free_tab(data->env);
			return ;
		}
		while (env[i][x])
		{
			data->env[i][x] = env[i][x];
			x++;
		}
		data->env[i][x] = '\0';
		i++;
	}
}

void	cpy_env_data(char **env, struct data *data)
{
	int	size;

	size = 0;
	while (env[size])
		size++;
	data->env = malloc(sizeof(char *) * (size + 1));
	if (!data->env)
		return ;
	data->env[size] = NULL;
	utils_cpy_env(env, data);
}

void	free_bon(t_bon *bon)
{
	if (!bon)
		return ;
	if (bon->path)
		free(bon->path);
	if (bon->av2)
		free(bon->av2);
	if (bon->valid_path)
		free(bon->valid_path);
	free(bon);
}

int	wile(t_bon *bon, struct data *data)
{
	while (data->path_split[bon->i])
	{
		bon->valid_path = ft_strjoin(data->path_split[bon->i], bon->av2);
		if (access(bon->valid_path, X_OK) == 0)
		{
			free(bon->path);
			free(bon->av2);
			free(bon->valid_path);
			free_tab(data->path_split);
			data->path_split = NULL;
			return (1);
		}
		bon->i++;
		free(bon->valid_path);
	}
	free(bon->path);
	free(bon->av2);
	if (data->path_split)
	{
		free_tab(data->path_split);
		data->path_split = NULL;
	}
	return (0);
}
