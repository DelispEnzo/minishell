/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:39:35 by elquesne          #+#    #+#             */
/*   Updated: 2025/05/17 19:39:36 by elquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*res;
	char	sep;

	sep = (char)c;
	res = NULL;
	while (*s != '\0')
	{
		if (*s == sep)
			res = ((char *)s);
		s++;
	}
	if (sep == '\0')
		res = ((char *)s);
	return (res);
}
