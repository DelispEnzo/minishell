/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:58:14 by enzo              #+#    #+#             */
/*   Updated: 2026/01/28 23:24:36 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

#include "../parser/parser.h"
#include "../utiles/utiles.h"
#include "../libft/libft.h"
#include "../tokens/token.h"

struct data
{
    // int code_erreur;
    char **result_split; //resultat de slpit de readline
    char **env; //copie de l'environement
    char **export_tab; // env vide pour export
    char **path_split; //chemin du path
};
struct token;
char *find_type(char *str, struct data *data);
void cpy_env_data(char **env, struct data *data);
char	**ft_split_mod(char const *s, char c);
// void fill_tokens(struct data *data, struct token *tokens, char **arg);

#endif
