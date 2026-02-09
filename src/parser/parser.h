/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elquesne <elquesne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:17:30 by enzo              #+#    #+#             */
/*   Updated: 2026/02/09 14:50:25 by elquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../built-in/built_in.h"
# include "../exec/exec.h"
# include "../lexer/lexer.h"
# include "../tokens/token.h"
# include "../utiles/utiles.h"

struct	commandes
{
	char				**argv;
	char				*value;

	char				*outfile;
	int					append_mode;

	char				*infile;
	char				*limiter;
	int					heredoc_mode;

	struct commandes	*next;
};

void					droite_utils(int fdfd, struct commandes *cmd);
int						size_argv(struct token *token);
struct token			*avance_token(struct token *token, int i);
int						gauche(struct commandes *cmd, struct token *tmp);
void					free_commande(struct commandes *cmd);
int						parser(struct token *token, struct data *data);

#endif
