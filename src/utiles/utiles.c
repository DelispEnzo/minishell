/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:22:04 by elquesne          #+#    #+#             */
/*   Updated: 2026/02/06 15:18:56 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"utiles.h"



void frate(struct data *data, char **arg)
{
	int i;

	i = 0;
	if (data->result_split)
	{
		while (data->result_split[i])
		{
			free(data->result_split[i]);
			i++;
		}
		free(data->result_split);
	}
	i = 0;
	if (arg)
	{
		while (arg[i])
		{
			free(arg[i]);
			i++;
		}
		free(arg);
	}
}

void free_all(char *line, struct data *data, struct token *tokens, char **arg) // OK
{
	int i;

	i = 0;
	free(line);
	if (data->env)
	{
		while (data->env[i])
		{
			free(data->env[i]);
			i++;
		}
		free(data->env);
	}
	frees(data);
	frate(data, arg);
	destroy_tokens(tokens);
	free(data);
	clear_history();
}

long long int ft_atoi_long_long(char *nptr)
{
    long long int    i;
    long long int    singe;
    long long int    n;

    singe = 1;
    n = 0;
    i = 0;
    while ((nptr[i] == 32) || (nptr[i] >= 9 && nptr[i] <= 13))
        i++;
    if (nptr[i] == '-' || nptr[i] == '+')
    {
        if (nptr[i] == '-')
            singe *= -1;
        i++;
    }
    while (nptr[i] >= '0' && nptr[i] <= '9')
    {
        n = n * 10 + (nptr[i] - '0');
        i++;
    }
    return (singe * n);
}

int ft_isdigit_line(char* str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (ft_isdigit(str[i]) == 0)
            return(1);
        i++;
    }
    return(0);
}

int have_spaces(char* str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if(str[i] == 32)
        {
            return(1);
        }
        i++;
    }
    return(0);
}
