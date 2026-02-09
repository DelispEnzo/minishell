#include"utiles.h"

int	ww(t_all *all)
{
	while (all->data->result_split[all->i] && all->etr == 0)
	{
		if (all->type)
		{
			free(all->type);
			all->type = NULL;
		}
		all->type = find_type(all->data->result_split[all->i], all->data);
		if (!all->type)
			return (free_1(all), 0);
		if (!all->arg[all->i])
			all->arg[all->i] = ft_strdup(all->type);

		if (ft_strncmp(all->type, "commande", 9) == 0)
		{
			all->j = all->i + 1;
			if (while_boucle(all) == 0)
				return (0);
		}

		free(all->type);
		all->type = NULL;
		all->i++;
	}
	return (1);
}

void	wh(t_all *all)
{
	while (all->data->result_split[all->k] && all->etr == 0)
	{
		all->value_env = chiant(all->data->result_split[all->k], all->data);
		all->value_env = suppr_quote(all->value_env);
		all->tokens = new_token(all->tokens, all->value_env, all->arg[all->k]);
		free(all->value_env);
		all->value_env = NULL;
		all->k++;
	}
	if (all->data->result_split)
	{
		free_tab(all->data->result_split);
		all->data->result_split = NULL;
	}
	if (all->arg)
	{
		free_tab(all->arg);
		all->arg = NULL;
	}
	if (all->etr == 0)
		parser(all->tokens, all->data);
	if (all->etr == 0)
		free_loop(all->data, &all->tokens, all->arg);
}

void	on_va_bien_tout_free(t_all *all)
{
	if (all->value_env)
		free(all->value_env);
	if (all->data->export_tab)
		free_tab(all->data->export_tab);
	if (all->data->path_split)
		free_tab(all->data->path_split);
	if (all->data->env)
		free_tab(all->data->env);
	if (all->data)
		free(all->data);
	if (all->tokens)
		destroy_tokens(all->tokens);
	free(all);
}

int dbl_pipe(char *str)
{
	int i;
	int x;

	x = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			x = i;
			x++;
			while (str[x] == ' ' || (str[x] == '\t' && str[x]))
				x++;
			if (str[x] == '|')
				return (ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2), 1);
			x = 0;
		}
		i++;
	}
	if (str[i - 1] == '|')
		return (1);
	return (0);
}

int	psg(t_all *all)
{
	if (all->line[0] == '\0')
		all->etr = 1;
	if (dbl_pipe(all->line) == 1)
		all->etr = 1;
	if (curcu(all) == 0)
		return (0);
	if (all->etr == 1 || !all->data->result_split || !all->data->result_split[0])
	{
		free_tab(all->data->result_split);
		all->data->result_split = NULL;
		return (1);
	}
	if (all->data->result_split)
	{
		if (if_0(all) == 0)
			return (0);
		if (if_2(all) == 0)
			return (0);
		if (ww(all) == 0)
			return (0);
		wh(all);
	}
	return (1);
}
