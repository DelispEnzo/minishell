/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:41:36 by elquesne          #+#    #+#             */
/*   Updated: 2025/05/17 19:41:37 by elquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*source;
	unsigned char	*destt;

	i = 0;
	destt = (unsigned char *)dest;
	source = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		if (dest < src)
		{
			destt[i] = source[i];
		}
		else
		{
			destt[n - 1 - i] = source[n - 1 - i];
		}
		i++;
	}
	return (dest);
}
