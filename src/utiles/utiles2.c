#include"utiles.h"

int	la_lenm(char *str)
{
	int		i;
	int		len;
	char	quote;

	i = 0;
	len = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && !quote)
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		else
			len++;
		i++;
	}
	return (len);
}

char	*suppr_quote(char *str)
{
	char	*resu;
	int		i;
	int		j;
	char	quote;

	if (!str)
		return (NULL);
	resu = malloc(sizeof(char) * (la_lenm(str) + 1));
	if (!resu)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && !quote)
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		else
			resu[j++] = str[i];
		i++;
	}
	resu[j] = '\0';
	free(str);
	return (resu);
}

void free_tab(char** tab)
{
	int i;

	i = 0;
	if (!tab)
		return;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return;
}

int ft_tab_len(char** tab) // Donne la taillle d'un tableau de tableau
{
	int i;

	i = 0;
	if (!tab)
		return (1);
	while (tab[i])
	{
		i++;
	}
	return(i);
}

void frees(struct data *data)
{
	int i;

	i = 0;
	if (data->path_split)
	{
		while (data->path_split[i])
		{
			free(data->path_split[i]);
			i++;
		}
		free(data->path_split);
	}
}
