#include"utiles.h"

int	init_all(t_all *all, char **env)
{
	if (data_init(all) == 0)
		return (0);
	all->tokens = NULL;
	all->line = NULL;
	all->arg = NULL;
	all->value_env = NULL;
	init_var(&all->etr, &all->k, &all->len, &all->j);
	cpy_env_data(env, all->data);
	if (!all->data->env)
	{
		free(all->data);
		return (0);
	}
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}

int	curcu(t_all *all)
{
	while ((all->line[all->k] == 32 || all->line[all->k] == '\t')
		&& all->line[all->k])
	{
		all->etr = 1;
		if ((all->line[all->k] != 32 && all->line[all->k] != '\t')
			&& all->line[all->k])
		{
			all->etr = 0;
			break ;
		}
		all->k++;
	}
	all->k = 0;
	if (*all->line && all->etr == 0)
		add_history(all->line);
	all->data->result_split = ft_split_mod(all->line, ' ');
	if (!all->data->result_split)
	{
		free(all->line);
		free_tab(all->data->env);
		free(all->data);
		return (0);
	}
	return (1);
}

int	if_0(t_all *all)
{
	int k;

	k = 0;
	all->len = ft_tab_len(all->data->result_split);
	all->arg = malloc(sizeof(char *) * (all->len + 1));
	if (!all->arg)
	{
		free_tab(all->data->result_split);
		free(all->line);
		free_tab(all->data->env);
		free(all->data);
		return (0);
	}
	while (k <= all->len)
	{
		all->arg[k] = NULL;
		k++;
	}
	all->arg[all->len] = NULL;
	all->i = 0;
	return (1);
}

int	if_2(t_all *all)
{
	all->type = find_type(all->data->result_split[all->i], all->data);
	if (!all->type)
	{
		free_tab(all->arg);
		free_tab(all->data->result_split);
		free(all->line);
		free_tab(all->data->env);
		free(all->data);
		return (0);
	}
	all->arg[all->i] = ft_strdup(all->type);
	return (1);
}

void	free_0(t_all *all)
{
	free(all->next_type);
	all->next_type = NULL;
	free_tab(all->arg);
	free(all->type);
	free_tab(all->data->result_split);
	free(all->line);
	free_tab(all->data->env);
	free(all->data);
}
