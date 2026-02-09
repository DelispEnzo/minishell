/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 12:09:52 by enzo              #+#    #+#             */
/*   Updated: 2026/02/09 14:28:08 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*petit(char *str)
{
	if (access(str, X_OK) == 0)
		return (ft_strdup(str));
	return (NULL);
}

static char	*get_path_env(struct data *data)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (data->env[i] != NULL)
	{
		if (ft_strncmp(data->env[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(data->env[i] + 5);
			break ;
		}
		i++;
	}
	return (path);
}

static int	split_path(struct data *data, char *path)
{
	if (data->path_split)
	{
		free_tab(data->path_split);
		data->path_split = NULL;
	}
	data->path_split = ft_split(path, ':');
	if (!data->path_split)
		return (0);
	return (1);
}

static char	*eh_valid_path(struct data *data, char *av2)
{
	int		i;
	char	*valid_path;

	i = 0;
	valid_path = NULL;
	while (data->path_split[i])
	{
		valid_path = ft_strjoin(data->path_split[i], av2);
		if (access(valid_path, X_OK) == 0)
			return (valid_path);
		i++;
		free(valid_path);
	}
	return (NULL);
}

char	*check_path(char *str, struct data *data)
{
	char	*path;
	char	*av2;
	char	*valid_path;

	path = NULL;
	av2 = NULL;
	if (bon(str))
		return (petit(str));
	path = get_path_env(data);
	if (!path)
		return (NULL);
	if (!split_path(data, path))
		return (free(path), NULL);
	free(path);
	if (ft_strncmp(str, "./", 2) != 0)
		av2 = ft_strjoin("/", str);
	else
		return (ft_strdup(str));
	valid_path = eh_valid_path(data, av2);
	free(av2);
	if (data->path_split)
		free_tab(data->path_split);
	data->path_split = NULL;
	return (valid_path);
}
