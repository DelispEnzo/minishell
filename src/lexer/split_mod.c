/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_mod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:59:57 by enzo              #+#    #+#             */
/*   Updated: 2026/02/11 13:26:49 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static size_t	count_words(char const *s, char c)
{
	size_t	words;
	size_t	i;
	char	quote;

	words = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		words++;
		quote = 0;
		while (s[i])
		{
			count_word_add_quto(&s, &quote, &i);
			if (quote && s[i] == quote)
				quote = 0;
			if (s[i] == c && !quote)
				break ;
			i++;
		}
	}
	return (words);
}

void	m2lt(t_adriano *adriano, char const *s, char c)
{
	adriano->start = adriano->index;
	adriano->quote = 0;
	while (s[adriano->index])
	{
		if ((s[adriano->index] == '\'' || s[adriano->index] == '\"')
			&& !adriano->quote)
			adriano->quote = s[adriano->index];
		else if (s[adriano->index] == adriano->quote)
			adriano->quote = 0;
		if (s[adriano->index] == c && !adriano->quote)
			break ;
		adriano->index++;
	}
}

void	wi(t_adriano *adriano, char const *s, char **tab)
{
	while (adriano->start < adriano->index)
		tab[adriano->i][adriano->j++] = s[adriano->start++];
	tab[adriano->i][adriano->j] = '\0';
	adriano->i++;
}

static void	set_mem(char **tab, char const *s, char c)
{
	t_adriano	*adriano;

	adriano = malloc(sizeof(t_adriano));
	if (!adriano)
		return ;
	adriano->i = 0;
	adriano->index = 0;
	while (s[adriano->index])
	{
		while (s[adriano->index] && s[adriano->index] == c)
			adriano->index++;
		if (s[adriano->index])
		{
			m2lt(adriano, s, c);
			tab[adriano->i] = malloc(sizeof(char) * (adriano->index
						- adriano->start + 1));
			if (!tab[adriano->i])
				return ;
			adriano->j = 0;
			adriano->quote = 0;
			wi(adriano, s, tab);
		}
	}
	tab[adriano->i] = NULL;
	free(adriano);
}

char	**ft_split_mod(char const *s, char c)
{
	size_t	words;
	char	**tab;

	words = count_words(s, c);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	set_mem(tab, s, c);
	tab[words] = NULL;
	return (tab);
}
