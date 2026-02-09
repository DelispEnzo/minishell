/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:38:10 by elquesne          #+#    #+#             */
/*   Updated: 2025/05/17 19:38:14 by elquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lenint(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	i++;
	return (i);
}

static void	fill_itoa(int n, char *res, int *i)
{
	if (n == -2147483648)
	{
		res[*i] = '-';
		(*i)++;
		res[*i] = '2';
		(*i)++;
		n = 147483648;
	}
	if (n < 0)
	{
		res[*i] = '-';
		(*i)++;
		n *= -1;
	}
	if (n > 9)
	{
		fill_itoa(n / 10, res, i);
	}
	res[*i] = n % 10 + '0';
	(*i)++;
}

char	*ft_itoa(int n)
{
	char	*res;
	int		i;
	int		y;

	i = 0;
	y = ft_lenint(n);
	res = malloc(sizeof(char) * y + 1);
	if (!res)
		return (NULL);
	fill_itoa(n, res, &i);
	res[i] = '\0';
	return (res);
}
