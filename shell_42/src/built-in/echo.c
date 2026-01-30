/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelispo <edelispo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 11:22:04 by enzo              #+#    #+#             */
/*   Updated: 2026/01/30 12:33:53 by edelispo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	is_flag_or_tozz(char *str)
{
	if (str[0] == '\0' || str[1] == '\0')
		return (0);
	if (str[0] == '-')
	{
		if (str[1] == 'n')
		{
			return (1);
		}
	}
	return (0);
}

int echo(char **argv)
{
	int i;

	i = 1;
	if (is_flag_or_tozz(argv[1]) == 1)
	{
		while (is_flag_or_tozz(argv[i]) == 1)
			i++;
		while (argv[i])
		{
			printf("%s", argv[i]);
			if (argv[i + 1] != NULL)
				printf(" ");
			i++;
		}
		return (0);
	}
	else
	{
		while (argv[i])
		{
			printf("%s", argv[i]);
			printf(" ");
			i++;
		}
		printf("\n");
	}
	return (0);
}
