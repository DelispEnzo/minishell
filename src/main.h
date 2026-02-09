/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elquesne <elquesne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 14:11:43 by enzo              #+#    #+#             */
/*   Updated: 2026/02/09 14:09:23 by elquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
#define MAIN_H

#include "built-in/built_in.h"
#include "lexer/lexer.h"
#include "signal/signal.h"

typedef struct all
{
	struct data		*data;
	struct token	*tokens;
	char			*line;
	char			*value_env;
	char			*type;
	char			*next_type;
	char			**arg;
	int				i;
	int				k;
	int				etr;
	int				j;
	int				len;
}	t_all;

typedef struct schiant
{
	int		i;
	int		j;
	char	*debut;
	char	*valh;
	char	*fin;
	char	*resultat;
	char	*tmp;
	char	*var;
}	t_chiant;

#endif
