#include"utiles.h"

int quote_statue(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && str[i + 1] == '\0')
			return (0);
		i++;
	}
	return (1);
}

char	*chiant(char *str, struct data *data)
{
	t_chiant	*schiant;
	char 		*res;

	schiant = malloc(sizeof(t_chiant));
	if (!schiant)
		return (NULL);
	schiant->i = 0;
	while (str[schiant->i])
	{
		if (str[schiant->i] == '$' && str[schiant->i + 1] != '\0'
			&& str[schiant->i + 1] != ' ' && str[schiant->i + 1] != '"' && quote_statue(str) == 1)
		{
			schiant->debut = ft_substr(str, 0, schiant->i);
			schiant->j = schiant->i + 1;
			while (str[schiant->j] && (ft_isalnum(str[schiant->j])
					|| str[schiant->j] == '_'))
				schiant->j++;
			kaaris(schiant, str, data);
			chiant2(schiant, str);
			res = schiant->resultat;
			free(schiant);
			return (res);
		}
		schiant->i++;
	}
	free(schiant);
	return (ft_strdup(str));
}

void	free_loop(struct data *data, struct token **tokens, char **arg)
{
	if (data->result_split)
	{
		free_tab(data->result_split);
		data->result_split = NULL;
	}
	if (arg)
	{
		free_tab(arg);
		arg = NULL;
	}
	if (*tokens)
	{
		destroy_tokens(*tokens);
		*tokens = NULL;
	}
}

int	data_init(t_all *all)
{
	all->data = malloc(sizeof(struct data));
	if (!all->data)
		return (0);
	all->type = NULL;
	all->next_type = NULL;
	all->data->path_split = NULL;
	all->data->result_split = NULL;
	all->data->env = NULL;
	all->data->export_tab = NULL;
	return (1);
}

void	init_var(int *etr, int *k, int *len, int *j)
{
	*etr = 0;
	*k = 0;
	*len = 0;
	*j = 0;
}
