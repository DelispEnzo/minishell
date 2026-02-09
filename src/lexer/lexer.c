/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:21:57 by enzo              #+#    #+#             */
/*   Updated: 2026/02/09 14:26:11 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	utils_check(t_bon *bon, char *str, int ret, struct data *data)
{
	if (data->path_split)
	{
		free_tab(data->path_split);
		data->path_split = NULL;
	}
	data->path_split = ft_split(bon->path, ':');
	bon->i = 0;
	bon->av2 = ft_strjoin("/", str);
	ret = wile(bon, data);
	free(bon);
	return (ret);
}

int	check_acces(char *str, struct data *data)
{
	t_bon	*bon;
	int		ret;

	ret = 0;
	bon = malloc(sizeof(t_bon));
	if (!bon)
		return (0);
	bon->path = NULL;
	bon->av2 = NULL;
	bon->valid_path = NULL;
	bon->i = 0;
	while (data->env[bon->i] != NULL)
	{
		if (ft_strncmp(data->env[bon->i], "PATH=", 5) == 0)
		{
			bon->path = ft_strdup(data->env[bon->i] + 5);
			if (!bon->path)
				return (0);
		}
		bon->i++;
	}
	if (!bon->path)
		return (free(bon), 0);
	utils_check(bon, str, ret, data);
	return (ret);
}

int	find_type_0(char *str, char **type)
{
	if (ft_strncmp(str, "echo", 5) == 0 || ft_strncmp(str, "cd", 2) == 0
		|| ft_strncmp(str, "pwd", 3) == 0 || ft_strncmp(str, "export", 7) == 0
		|| ft_strncmp(str, "unset", 6) == 0 || ft_strncmp(str, "env", 4) == 0
		|| ft_strncmp(str, "exit", 5) == 0)
	{
		*type = ft_strdup("commande");
		return (1);
	}
	else if (ft_strncmp(str, "|", 2) == 0)
	{
		*type = ft_strdup("pipe");
		return (1);
	}
	else if (ft_strncmp(str, ">>", 3) == 0)
	{
		*type = ft_strdup("dgreat");
		return (1);
	}
	return (0);
}

int	find_type_1(char *str, char **type, struct data *data)
{
	if (ft_strncmp(str, ">", 2) == 0)
	{
		*type = ft_strdup("great");
		return (1);
	}
	else if (ft_strncmp(str, "<<", 3) == 0)
	{
		*type = ft_strdup("dless");
		return (1);
	}
	else if (ft_strncmp(str, "<", 2) == 0)
	{
		*type = ft_strdup("less");
		return (1);
	}
	else if (check_acces(str, data) == 1)
	{
		*type = ft_strdup("commande");
		return (1);
	}
	return (0);
}

char	*find_type(char *str, struct data *data)
{
	char	*type;

	type = NULL;
	if (find_type_0(str, &type) == 1)
		return (type);
	else if (find_type_1(str, &type, data) == 1)
		return (type);
	else
	{
		type = ft_strdup("mot");
		return (type);
	}
	return (NULL);
}
