#include "lexer/lexer.h"
#include "signal/signal.h"
#include "built-in/built_in.h"

void free_loop(struct data *data, struct token **tokens, char **arg)
{
    int i;

    if (data->result_split)
    {
        for (i = 0; data->result_split[i]; i++)
            free(data->result_split[i]);
        free(data->result_split);
        data->result_split = NULL;
    }
    if (arg)
    {
        free(arg); 
    }
    if (*tokens)
    {
        destroy_tokens(*tokens);
        *tokens = NULL;
    }
}

int main(int ac, char **av, char **env)
{
    struct data *data;
    struct token *tokens = NULL;
    char *line;
    char *type;
    char *next_type;
    char **arg;
    int i;
    int k;
    int j;
    int len;

    (void)av; (void)ac;
    data = malloc(sizeof(struct data));
    if (!data)
        return (1);
    k = 0;
    len = 0;
    j = 0;
    type = NULL;
    next_type = NULL;
    data->path_split = NULL;
    data->result_split = NULL;
    data->env = NULL;
    cpy_env_data(env, data);
    
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);

    while (1)
    {
        line = readline("minishell$ ");
        if (!line) break;
        if (*line) add_history(line);

        data->result_split = ft_split_mod(line, ' ');
        if (data->result_split)
        {
            len = ft_tab_len(data->result_split);
            arg = malloc(sizeof(char*) * (len + 1));
            if (!arg) break;
            arg[len] = NULL;

            i = 0;
            while (data->result_split[i])
            {
                type = find_type(data->result_split[i], data);
                arg[i] = type; 
                if (ft_strcmp(type, "commande") == 0)
                {
                    j = i + 1;
                    while (data->result_split[j])
                    {
                        next_type = find_type(data->result_split[j], data);
                        if (ft_strcmp(next_type, "pipe") == 0 || ft_strcmp(next_type, "great") == 0) 
                        {
                            free(next_type);
                            break;
                        }
                        arg[j] = ft_strdup("arg");
                        free(next_type);
                        j++;
                    }
                    i = j - 1;
                }
                i++;
            }
            while (data->result_split[k])
            {
                tokens = new_token(tokens, data->result_split[k], arg[k]);
                k++;
            }
			//////////////////////////////////////////////////////////////////////////////////////////////////////
			// if (tokens && ft_strcmp(tokens->value, "export") == 0)
			// {
			// 	ft_export(tokens, data);
			// }                                                                   sert a tester les builtin   <-------------------------------------------------------
			// if (tokens && ft_strcmp(tokens->value, "exit") == 0)
			// {
			// 	ft_exit(tokens);
			// }
			/////////////////////////////////////////////////////////////////////////////////////////////////////
            free_loop(data, &tokens, arg);
        }
        free(line);
    }
    free_all(NULL, data, NULL, NULL); 
    return (0);
}
