/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 11:22:04 by enzo              #+#    #+#             */
/*   Updated: 2026/02/06 00:49:09 by enzo             ###   ########.fr       */
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
			if (str[2] == '\0' || str[2] == 'n')
				return (1);
		}
	}
	return (0);
}

int echo(char **argv)
{
	int i;
	int x;
	int n_flag;

	x = 0;
	n_flag = 0;
	if (!argv[1])
	{
		printf("\n");
		return (0);
	}
	n_flag = is_flag_or_tozz(argv[1]);
	i = 1;
	while (is_flag_or_tozz(argv[i]) == 1 && argv[i])
		i++;
	while (argv[i])
	{
		x = 0;
		while (argv[i][x])
		{
			printf("%c", argv[i][x]);
			x++;
		}
		if (argv[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n_flag == 0)
		printf("\n");
	return (0);
}
