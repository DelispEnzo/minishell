/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:38:25 by elquesne          #+#    #+#             */
/*   Updated: 2025/05/17 19:38:27 by elquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*destt;
	unsigned char	*srcc;

	if (dest == NULL && src == NULL)
		return (dest);
	destt = (unsigned char *)dest;
	srcc = (unsigned char *)src;
	while (n > 0)
	{
		*destt = *srcc;
		destt++;
		srcc++;
		n--;
	}
	return (dest);
}
