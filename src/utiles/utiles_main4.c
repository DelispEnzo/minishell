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

static int token_has_quote(char *s)
{
	int i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		return (1);
		i++;
	}
	return (0);
}

void	wh(t_all *all)
{
	int quoted;
	while (all->data->result_split[all->k] && all->etr == 0)
	{
		quoted = token_has_quote(all->data->result_split[all->k]);
		all->value_env = chiant(all->data->result_split[all->k], all->data);
		all->value_env = suppr_quote(all->value_env);
		all->tokens = new_token(all->tokens, all->value_env, all->arg[all->k], quoted);
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
		parser(all);
	if (all->etr == 0)
		free_loop(all->data, &all->tokens, all->arg);
}

void free_all_on(t_all *all)
{
		if (all->data->env)
	{
		free_tab(all->data->env);
		all->data->env = NULL;
	}
	if (all->data)
	{
		free(all->data);
		all->data = NULL;
	}
	if (all->tokens)
	{
		destroy_tokens(all->tokens);
		all->tokens = NULL;
	}
	if (all->line)
		free(all->line);
	if (all->type)
		free(all->type);
	if (all->next_type)
		free(all->next_type);
	if (all->arg)
		free_tab(all->arg);
	free(all);
}

void	on_va_bien_tout_free(t_all *all)
{
	if (all->value_env)
	{
		free(all->value_env);
		all->value_env = NULL;
	}
	if (all->data->export_tab)
	{
		free_tab(all->data->export_tab);
		all->data->export_tab = NULL;
	}
	if (all->data->path_split)
	{
		free_tab(all->data->path_split);
		all->data->path_split = NULL;
	}
	free_all_on(all);
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

int pipe_close(t_all *all)
{
	int i;
	char *str;
	char der;

	str = all->line;
	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9')
				|| (str[i] == '|'))
			der = str[i];
		i++;
	}
	if (der == '|')
		return (0);
	return (1);
}

int check_read_result(char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while ((str[i] == ' ' || str[i] == '\t') && str[i])
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}
char *pipe_heardoc(t_all *all)
{
	char *rea;
	char *res;
	char *res2;

	rea = NULL;
	while (check_read_result(rea) != 1)
		rea = readline("pipe> ");
	res = ft_strjoin(all->line, " ");
	res2 = ft_strjoin(res, rea);
	free(res);
	return (res2);
}

int	psg(t_all *all)
{
	if (pipe_close(all) == 0)
		all->line = pipe_heardoc(all);
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
