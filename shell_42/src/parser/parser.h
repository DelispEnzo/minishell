#ifndef PARSER_H
#define PARSER_H

struct commandes
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
#include "../built-in/built_in.h"
#include "../utiles/utiles.h"
#include "../tokens/token.h"
#include "../lexer/lexer.h"

#endif
