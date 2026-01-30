#include "lexer/lexer.h"
#include "signal/signal.h"
#include "built-in/built_in.h"

void free_loop(struct data *data, struct token **tokens, char **arg)
{
    int i;

    i = 0;
    if (data->result_split)
    {
        free_tab(data->result_split);
        data->result_split = NULL;
    }
    if (arg)
    {
        free_tab(arg);
        arg = NULL;
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
    int etr;
    int j;
    int len;

    (void)av; (void)ac;
    data = malloc(sizeof(struct data));
    if (!data)
        return (1);
    etr = 0;
    k = 0;
    len = 0;
    j = 0;
    type = NULL;
    next_type = NULL;
    data->path_split = NULL;
    data->result_split = NULL;
    data->env = NULL;
    data->export_tab = NULL;
    cpy_env_data(env, data);
    if (!data->env)
    {
        free(data);
        return(1);
    }
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
    while (1)
    {
        etr = 0;
        line = readline("minishell$ ");
        if (!line)
        {
            free_tab(data->env);
            free(data);
            return(1);
        }
        if(line[0] == '\0')
            etr = 1;
        if (*line && etr == 0)
            add_history(line);
        k = 0;
        data->result_split = ft_split_mod(line, ' ');
        if(!data->result_split)
        {
            free(line);
            free_tab(data->env);
            free(data);
            return(1);
        }
        if (data->result_split)
        {
            len = ft_tab_len(data->result_split);
            arg = malloc(sizeof(char*) * (len + 1));
            if (!arg)
            {
                free_tab(data->result_split);
                free(line);
                free_tab(data->env);
                free(data);
                return(1);
            }
            arg[len] = NULL;

            i = 0;
            while (data->result_split[i] && etr == 0)
            {
                type = find_type(data->result_split[i], data);
                if(!type)
                {
                    free(arg);
                    free_tab(data->result_split);
                    free(line);
                    free_tab(data->env);
                    free(data);
                    return(1);
                }
                arg[i] = ft_strdup(type);
                if (ft_strncmp(type, "commande", 9) == 0)
                {
                    j = i + 1;
                    while (data->result_split[j])
                    {
                        next_type = find_type(data->result_split[j], data);
                        if(!next_type)
                        {
                            free(type);
                            free(arg);
                            free_tab(data->result_split);
                            free(line);
                            free_tab(data->env);
                            free(data);
                            return(1);
                        }
                        if (ft_strncmp(next_type, "pipe", 5) == 0 || ft_strncmp(next_type, "great", 6) == 0)
                        {
                            free(next_type);
                            break;
                        }
                        arg[j] = ft_strdup("arg");
                        if(!arg[j])
                        {
                            free(next_type);
                            free_tab(arg);
                            free(type);
                            free_tab(data->result_split);
                            free(line);
                            free_tab(data->env);
                            free(data);
                            return(1);
                        }
                        free(next_type);
                        j++;
                    }
                    i = j - 1;
                }
                if(type && etr == 0)
                {
                    free(type);
                    type = NULL;
                }
                i++;
            }
            while (data->result_split[k] && etr == 0)
            {
                tokens = new_token(tokens, data->result_split[k], arg[k]);
                k++;
            }
            if(data->result_split)
            {
                free_tab(data->result_split);
                data->result_split = NULL;
            }
            if(arg)
            {
                free_tab(arg);
                arg = NULL;
            }
            if (etr == 0)
                parser(tokens, data);
            if (etr == 0)
                free_loop(data, &tokens, arg);
        }
        free(line);
    }
    if (data->export_tab)
        free_tab(data->export_tab);
    if(data->path_split)
        free_tab(data->path_split);
    if(data->env)
        free_tab(data->env);
    if(data)
        free(data);
    if(tokens)
        free(tokens);
    return (0);
}
