/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:52:33 by enzo              #+#    #+#             */
/*   Updated: 2026/02/10 12:07:03 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-in/built_in.h"
#include "lexer/lexer.h"
#include "main.h"
#include "signal/signal.h"

void	free_1(t_all *all)
{
	free(all->type);
	free_tab(all->arg);
	free_tab(all->data->result_split);
	free(all->line);
	free_tab(all->data->env);
	free(all->data);
}

int	while_boucle(t_all *all)
{
	while (all->data->result_split[all->j])
	{
		all->next_type = find_type(all->data->result_split[all->j], all->data);
		if (!all->next_type)
			return (free_1(all), 1);
		if (ft_strncmp(all->next_type, "pipe", 5) == 0
			|| ft_strncmp(all->next_type, "great", 6) == 0
			|| ft_strncmp(all->next_type, "dgreat", 7) == 0
			|| ft_strncmp(all->next_type, "less", 5) == 0
			|| ft_strncmp(all->next_type, "dless", 6) == 0)
		{
			free(all->next_type);
			all->next_type = NULL;
			break ;
		}
		all->arg[all->j] = ft_strdup("arg");
		if (!all->arg[all->j])
			return (free_0(all), 0);
		free(all->next_type);
		all->next_type = NULL;
		all->j++;
	}
	all->i = all->j - 1;
	return (1);
}

void free_data(struct data *data)
{
	if(!data)
		return ;
	if (data->env)
		free_tab(data->env);
	if(data->export_tab)
		free_tab(data->export_tab);
	if(data->path_split)
		free_tab(data->path_split);
	if(data->result_split)
		free(data->result_split);
	free(data);
}

int	main(int ac, char **av, char **env)
{
	t_all	*all;

	(void)av;
	(void)ac;
	all = malloc(sizeof(t_all));
	if (!all)
		return (1);
	if (init_all(all, env) == 0)
		return (free(all), 0);
	while (1)
	{
		all->etr = 0;
		all->line = readline("minishell$ ");
		if (!all->line)
		{
			return (on_va_bien_tout_free(all)/*, DIXDOUZEQUATORZBUREAUX(all)*/,1);
		}
		if (psg(all) == 0)
			return (on_va_bien_tout_free(all)/*, DIXDOUZEQUATORZBUREAUX(all)*/,1);
		free(all->line);
	}
	on_va_bien_tout_free(all);
	return (DIXDOUZEQUATORZBUREAUX(all), 0);
}
