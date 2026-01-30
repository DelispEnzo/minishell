/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelispo <edelispo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:21:57 by enzo              #+#    #+#             */
/*   Updated: 2026/01/30 17:07:34 by edelispo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"



void cpy_env_data(char **env, struct data *data) // ok
{
	int i;
	int x;
	int size;


	i = 0;
	size = 0;
	x = 0;
	while (env[size])
		size++;
	data->env = malloc(sizeof(char *) * (size + 1));
	if (!data->env)
		return;
	data->env[size] = NULL;
	while (env[i])
	{
		x = 0;
		data->env[i] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		if (!data->env[i])
		{
			free_tab(data->env);
			return;
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

int check_acces(char *str, struct data *data) // verifie si la commande existe ou non
{
	int i;
	char *path;
	char	*av2;
	char	*valid_path;

	i = 0;
	while (data->env[i] != NULL)
	{
		if (ft_strncmp(data->env[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(data->env[i]);
			if (!path)
				return (0);
		}
		i++;
	}
	if(data->path_split)
		free_tab (data->path_split);
	data->path_split = ft_split(path, ':');
	i = 0;
	av2 = ft_strjoin("/", str);
	valid_path = NULL;
	while (data->path_split[i])
	{
		valid_path = ft_strjoin(data->path_split[i], av2);
		if (access(valid_path, X_OK) == 0)
		{
			free(path);
			free(av2);
			free(valid_path);
			return (1);
		}
		i++;
		free(valid_path);
	}
	free(path);
	free(av2);
	return (0);
}

char *find_type(char *str, struct data *data) // cherche les type
{
	char *type;

	type = NULL;
	if (ft_strncmp(str, "echo", 5) == 0 || ft_strncmp(str, "cd", 2) == 0 || ft_strncmp(str, "pwd", 3) == 0  || ft_strncmp(str, "export", 7) == 0  || ft_strncmp(str, "unset", 6) == 0  || ft_strncmp(str, "env", 4) == 0  || ft_strncmp(str, "exit", 5) == 0 )
	{
		type = ft_strdup("commande");
		return (type);
	}
	else if (ft_strncmp(str, "|", 2) == 0)
	{
		type = ft_strdup("pipe");
		return (type);
	}
	else if (ft_strncmp(str, ">>", 3) == 0)
	{
		type = ft_strdup("dgreat");
		return(type);
	}
	else if (ft_strncmp(str, ">", 2) == 0)
	{
		type = ft_strdup("great");
		return(type);
	}
	else if (ft_strncmp(str, "<<", 3) == 0)
	{
		ft_strdup("dless");
		return(type);
	}
	else if (ft_strncmp(str, "<", 2) == 0)
	{
		type = ft_strdup("less");
		return(type);
	}
	else if (check_acces(str, data) == 1)
	{
		type = ft_strdup("commande");
		return (type);
	}
	else
	{
		type = ft_strdup("mot");
		return (type);
	}
	return (NULL);
}
