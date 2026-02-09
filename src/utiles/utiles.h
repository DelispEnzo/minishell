#ifndef UTILES_H
# define UTILES_H

# include "../lexer/lexer.h"
# include "../libft/libft.h"
# include "../main.h"
# include  "../exec/exec.h"
# include "../tokens/token.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

struct data;
struct token;


int				while_boucle(t_all *all);
void			free_1(t_all *all);
int				ww(t_all *all);
void			wh(t_all *all);
void			on_va_bien_tout_free(t_all *all);
int				dbl_pipe(char *str);
int				psg(t_all *all);
int				init_all(t_all *all, char **env);
int				curcu(t_all *all);
int				if_0(t_all *all);
int				if_2(t_all *all);
void			free_0(t_all *all);
void			init_var(int *etr, int *k, int *len, int *j);
int				data_init(t_all *all);
void			free_loop(struct data *data, struct token **tokens, char **arg);
char			*chiant(char *str, struct data *data);
int				quote_statue(char *str);
void			kaaris(t_chiant *schiant, char *str, struct data *data);
void			chiant2(t_chiant *schiant, char *str);
char			*get_env_val(char *var, struct data *data);
void			DIXDOUZEQUATORZBUREAUX(t_all *all);
void			free_da(t_all *all);
void			frees(struct data *data);
int				ft_tab_len(char **tab);
void			free_tab(char **tab);
char			*suppr_quote(char *str);
int				la_lenm(char *str);
void			free_all(char *line, struct data *data, struct token *tokens,
					char **arg);
long long int	ft_atoi_long_long(char *nptr);
int				ft_isdigit_line(char *str);
int				have_spaces(char *str);
char			*suppr_quote(char *str);

#endif
