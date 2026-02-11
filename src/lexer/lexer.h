/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:58:14 by enzo              #+#    #+#             */
/*   Updated: 2026/02/11 13:27:33 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../libft/libft.h"
# include "../parser/parser.h"
# include "../tokens/token.h"
# include "../utiles/utiles.h"

struct		data
{
	int		return_code;
	char **result_split; // resultat de slpit de readline
	char **env;          // copie de l'environement
	char **export_tab;   // env vide pour export
	char **path_split;   // chemin du path
};

typedef struct bon
{
	int		i;
	char	*path;
	char	*av2;
	char	*valid_path;
}			t_bon;

typedef struct adriano
{
	size_t	i;
	size_t	start;
	size_t	index;
	size_t	j;
	char	quote;
}			t_adriano;

struct token;
void		count_word_add_quto(char const **s, char *quote, size_t *i);
void		free_bon(t_bon *bon);
void		utils_cpy_env(char **env, struct data *data);
void		cpy_env_data(char **env, struct data *data);
int			wile(t_bon *bon, struct data *data);
char		*find_type(char *str, struct data *data);
char		**ft_split_mod(char const *s, char c);

#endif
