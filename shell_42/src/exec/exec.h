#ifndef EXEC_H
# define EXEC_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../tokens/token.h"
#include "../lexer/lexer.h"
#include <fcntl.h>
#include <readline/readline.h>

struct commande
{
    char **argv;
    char *value;

    // --- Gestion Sortie (Output) ECRAN ---
    char *outfile;     // Nom du fichier
    int  append_mode;  // 0 si '>', 1 si '>>' (AJOUT)

	// --- Gestion Entrée (Input) Clavier
	char *infile;      // Nom du fichier pour '<'
	char *limiter;     // Mot de fin pour '<<' (Heredoc)
	int  heredoc_mode; // 1 si '<<', 0 sinon

	struct commande *next;
};

// --- PROTOTYPES ---
int execution(struct commande *cmd, struct token *tokens);
int parser(struct token *tokens, struct data *data);
int gestion_heredoc(char *delimiteur);
void echo(char **argv);

#endif
