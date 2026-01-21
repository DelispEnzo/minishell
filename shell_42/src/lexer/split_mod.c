/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_mod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:59:57 by enzo              #+#    #+#             */
/*   Updated: 2026/01/21 16:59:58 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static size_t	count_words(char const *s, char c)
{
	size_t	words;
	size_t	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\"')
		{
			i++;
			while (s[i] && (s[i] != '\"'))
			{
				i++;
			}
			words++;
		}
		else if (s[i] == '\'')
		{
			i++;
			while (s[i] && (s[i] != '\''))
			{
				i++;
			}
			words++;
		}
		else if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			words++;
		}
		i++;
	}
	return (words);
}

static void	fill_tab(char *new, char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] == '\"')
		{
			new[i] = s[i];
			i++;
			while (s[i] && (s[i] != '\"'))
			{
				new[i] = s[i];
				i++;
			}
			new[i] = '\"';
			i++;
			break;
		}
		else if (s[i] == '\'')
		{
			new[i] = s[i];
			i++;
			while (s[i] && (s[i] != '\''))
			{
				new[i] = s[i];
				i++;
			}
			new[i] = '\'';
			i++;
			break;
		}
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
}

static void	set_mem(char **tab, char const *s, char c)
{
	size_t	count;
	size_t	index;
	size_t	i;

	index = 0;
	i = 0;
	while (s[index])
	{
		count = 0;
		while (s[count + index] && s[count + index] != c)
		{
			if (s[count + index] == '\"')
			{
				count++;
				while (s[count + index] && (s[count + index] != '\"'))
				{
					count++;
				}
			}
			else if (s[count + index] == '\'')
			{
				count++;
				while (s[count + index] && (s[count + index] != '\''))
				{
					count++;
				}
			}
			count++;
		}
		if (count > 0)
		{
			tab[i] = malloc(sizeof(char) * (count + 1));
			if (!tab[i])
				return ;
			fill_tab(tab[i], (s + index), c);
			i++;
			index = index + count;
		}
		else
			index++;
	}
	tab[i] = 0;
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**tab;

	words = count_words(s, c);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	set_mem(tab, s, c);
	return (tab);
}

// int main(void)
// {
// 	char *line;
// 	char **tab;
// 	int i;

// 	i = 0;
// 	while (1)
// 	{
// 		line = readline("minishell$ ");
//         if (!line)   // Ctrl-D
//             break;

// 		printf("Tu as tapé: %s\n", line);
// 		tab = ft_split(line, ' ');
// 		while (tab[i])
// 		{
// 			printf("tab[%d] = %s\n", i, tab[i]);
// 			i++;
// 		}
// 	}
//     return 0;
// }
