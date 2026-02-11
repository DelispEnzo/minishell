/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 17:51:55 by enzo              #+#    #+#             */
/*   Updated: 2026/02/11 13:23:31 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../lexer/lexer.h"
# include "../parser/parser.h"
# include "../tokens/token.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "../main.h"

typedef struct	s_principal
{
	struct commandes	*commande;
	pid_t				pid;
	int					statue;
	pid_t				eh;
	pid_t				der_pid;
	int					fd[2];
}	t_principal;

typedef struct	s_enfant
{
	struct commandes	*commande;
	struct token		*tokens;
	struct commandes	*cmd;
	struct data			*data;
	int					*fd;
	int					prev;
	struct s_principal  *princ;
}	t_enfant;

void					init_enfant_1(t_enfant *enfant, struct data *data, int *fd);
void					no_valid_path(t_enfant *enfant, t_all *all, char *valid_path);
void					free_principal(t_principal *bon);
int						bon(char *str);
int						execution(struct commandes *cmd, struct data *data);
int						execution_2(struct commandes *cmd, struct data *data);
void					free_machin_truc(struct token *tokens,
							struct data *data, struct commandes *cmd);
void					valid_null(struct commandes *commande,
							char *valid_path);
void					commande_parent(struct commandes *cmd,
							struct data *data, int prev);
void					exevv(t_enfant *enfant, char *valid_path, t_all *all);
t_enfant				*init_enfant_0(struct commandes *commande,
							struct token *tokens, struct commandes *cmd);
char					*check_path(char *str, struct data *data);
void					free_machin_truc(struct token *tokens,
							struct data *data, struct commandes *cmd);
void					les_if(t_enfant *enfant, int *fd_heredoc);
void					petit_if(t_enfant *enfant, int *flag, int *fd_out);
void					eh_if(t_enfant *enfant, int *fd_in);
int						execution(struct commandes *cmd, struct data *data);
int						exec(t_all *all,
							struct commandes *cmd);
int						gestion_heredoc(char *delimiteur, int expand, struct data *data);

#endif
