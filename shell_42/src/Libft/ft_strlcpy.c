/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:42:53 by elquesne          #+#    #+#             */
/*   Updated: 2025/05/17 19:42:54 by elquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	i;
	int		len_src;
	char	*srcc;

	srcc = ft_strdup(src);
	len_src = ft_strlen(src);
	i = 0;
	if (destsize == 0)
		return (len_src);
	while (i < destsize - 1 && src[i])
	{
		dest[i] = srcc[i];
		i++;
	}
	dest[i] = '\0';
	return ((size_t)len_src);
}
