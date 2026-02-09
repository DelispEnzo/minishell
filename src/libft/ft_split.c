/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:08:11 by elquesne          #+#    #+#             */
/*   Updated: 2025/05/16 19:09:41 by elquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_liberer(char **res, int i)
{
	while (i >= 0)
	{
		free(res[i]);
		i--;
	}
	free(res);
}

static int	ft_compte_les_mots(const char *s, char c)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	if (!s[i])
		return (y);
	if (s[i] != c && s[i] != '\0')
	{
		i++;
		y++;
	}
	while (s[i])
	{
		if (s[i - 1] == c && s[i] != c)
			y++;
		i++;
	}
	return (y);
}

static void	ft_remplir_separation(char **res, char const *str, char c)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (str[y])
	{
		if ((y == 0 && str[y] != c) || (str[y] != c && str[y - 1] == c))
		{
			while (str[y] != c && str[y])
				res[i][x++] = str[y++];
			res[i][x] = '\0';
			i++;
			x = 0;
		}
		else
			y++;
	}
	res[i] = NULL;
}

static int	ft_longeur_des_mots(const char *s, char c, int i)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	while (y <= i)
	{
		if ((x == 0 && s[x] != c) || (s[x] != c && s[x - 1] == c))
			y++;
		x++;
	}
	y = 0;
	x = x - 1;
	while (s[x] != c && s[x])
	{
		y++;
		x++;
	}
	return (y);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		y;
	char	**res;

	if (!s)
		return (NULL);
	i = 0;
	y = ft_compte_les_mots(s, c);
	res = malloc(sizeof(char *) * (y + 1));
	if (!res)
		return (NULL);
	while (i < y)
	{
		res[i] = malloc(sizeof(char) * (ft_longeur_des_mots(s, c, i) + 1));
		if (!res[i])
		{
			ft_liberer(res, i);
			return (NULL);
		}
		i++;
	}
	ft_remplir_separation(res, s, c);
	return (res);
}
