#include"utiles.h"

void	free_da(t_all *all)
{
	if (all->data->result_split)
		free_tab(all->data->result_split);
	if (all->data->path_split)
		free_tab(all->data->path_split);
	if (all->data->export_tab)
		free_tab(all->data->export_tab);
	if (all->data->env)
		free_tab(all->data->env);
	free(all->data);
	all->data = NULL;
}
void	DIXDOUZEQUATORZBUREAUX(t_all *all)
{
	if (!all)
	{
		return;
	}
	if (all->line)
		free(all->line);
	if (all->value_env)
		free(all->value_env);
	if (all->type)
		free(all->type);
	if (all->next_type)
		free(all->next_type);
	if (all->arg)
		free_tab(all->arg);
	free(all);
}

char	*get_env_val(char *var, struct data *data)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], var, len) == 0 && data->env[i][len] == '=')
			return (ft_strdup(data->env[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}

void	chiant2(t_chiant *schiant, char *str)
{
	schiant->fin = ft_strdup(str + schiant->j);
	schiant->tmp = ft_strjoin(schiant->debut, schiant->valh);
	schiant->resultat = ft_strjoin(schiant->tmp, schiant->fin);
	free(schiant->debut);
	free(schiant->valh);
	free(schiant->fin);
	free(schiant->tmp);
}

void	kaaris(t_chiant *schiant, char *str, struct data *data)
{
	if (str[schiant->i + 1] == '?')
	{
		schiant->valh = ft_itoa(data->return_code);
		schiant->j = schiant->i + 2;
	}
	else
	{
		schiant->var = ft_substr(str, schiant->i + 1, schiant->j - (schiant->i
					+ 1));
		schiant->valh = get_env_val(schiant->var, data);
		free(schiant->var);
	}
}
