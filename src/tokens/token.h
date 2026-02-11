#ifndef TOKEN_H
# define TOKEN_H

# include "../lexer/lexer.h"
# include "../libft/libft.h"
# include "../utiles/utiles.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

struct token
{
	int quoted;
	char *value;
	char *type;
	struct token *next;
};

void	destroy_tokens(struct token *tokens);
struct token	*new_token(struct token *tokens, char *value, char *type,
		int quoted);

#endif
