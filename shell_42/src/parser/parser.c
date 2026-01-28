/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elquesne <elquesne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:27:51 by elquesne          #+#    #+#             */
/*   Updated: 2026/01/28 17:38:26 by elquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

void init_commande(struct commandes *commande)
{
    commande->append_mode = 0;
    commande->heredoc_mode = 0;
    commande->infile = NULL;
    commande->limiter = NULL;
    commande->next = NULL;
    commande->outfile = NULL;
    commande->value = NULL;
}

// void free_commandes(struct commandes *commandes)
// {
//     struct commandes *tmp;
    
    
//     if(commandes->next != NULL)
//     {
//         while (commandes->next != NULL)
//         {
//             tmp = commandes->next;
//             free_tab(commandes->args);
//             free(commandes);
//             commandes = tmp;
//         }
//     }
//     else
//     {
//         if(commandes->args)
//         {
//             free_tab(commandes->args);
//         }
//         free(commandes);
//     }
// }



int is_separateur(char* token_type)
{
	if (ft_strncmp(token_type, "dgreat", 6) == 0)
		return (1);
	else if (ft_strncmp(token_type, "great", 6) == 0)
		return (1);
	else if (ft_strncmp(token_type, "dless", 6) == 0)
		return (1);
	else if (ft_strncmp(token_type, "less", 5) == 0)
		return (1);
    else
        return(0);
}

void fill_args(struct commandes *commandes, struct token *tokens, int index)
{
    struct token *token;
    struct commandes *commande;
    int i;
    
    token = tokens;
    commande = commandes;
    i = 0;
    while (i <= index)
    {
        while (token != NULL && ft_strcmp(token->type, "pipe") != 0)
            token = token->next;
        i++;
    }
    if(token->next != NULL)
        token = token->next;
    i = 0;
    while (commande->argv[i])
    {
        if(is_separateur(token->type) == 1)
        {
            if(ft_strcmp(token->value, "<<") != 0)
            {
                commande->heredoc_mode = 1;
                commande->limiter = token->next->value;
                if(commande->limiter == NULL || is_separateur(commande->limiter) == 1 || ft_strcmp(commande->limiter, "|") == 0)
                {
                    printf("minishell: syntax error near unexpected token `%s'", commande->limiter);
                    exit(2);
                }
            }
            else if(ft_strcmp(token->value, "<") != 0)
                commande->infile = token->next->value;
        }
        else
            commande->argv[i] = ft_strdup(token->value);
        token = token->next;
        if(token != NULL && ft_strcmp(token->type, "pipe") == 0)
            break;
        i++;
    }
    
}

void parsin_general(struct data *data, struct token *tokens)
{
    struct token *token;
    struct commandes* commandes;
    int i;
    int y;
    int x;
    
    x = 0;
    y = 0;
    i = 0;
    while(token != NULL)
    {
        x = 0;
        while (token != NULL && ft_strcmp(token->type, "pipe") != 0)
        {
            token = token->next;
            x++;
        }
        commandes = malloc(sizeof(struct commandes));
        if(!commandes)
            return(free_commandes(commandes));.
        init_commande(commandes);
        commandes->argv = malloc(sizeof(char *) * (x + 1));
        if(!commandes)
            return(free_commandes(commandes));
        commandes->argv[x] = NULL;
        fill_args(commandes , tokens, y);
        y++;
        // token = token->next;
    }
}
