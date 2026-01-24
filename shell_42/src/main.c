#include "lexer/lexer.h"
#include "signal/signal.h"

void free_all(char *line, struct data *data, struct token *tokens, char **arg) // OK
{
	int i;

	i = 0;
	free(line);
	if (data->env)
	{
		while (data->env[i])
		{
			free(data->env[i]);
			i++;
		}
		free(data->env);
	}
	i = 0;
	if (data->path_split) {
		while (data->path_split[i])
		{
			free(data->path_split[i]);
			i++;
		}
		free(data->path_split);
	}
	i = 0;
	if (data->result_split)
	{
		while (data->result_split[i])
		{
			free(data->result_split[i]);
			i++;
		}
		free(data->result_split);
	}
	i = 0;
	if (arg)
	{
		while (arg[i])
		{
			free(arg[i]);
			i++;
		}
	}

	destroy_tokens(tokens);
	free(data);
}

int main(int ac, char **av, char **env)
{
	struct data *data;
	struct token *tokens;
	char *line;
	int i;
	char **arg;
	char *tmp;

	(void)av;
	(void)ac;
	arg = NULL;
	// malloc tableau arg**
	i = 0;
	tokens = NULL;
	data = malloc(sizeof(struct data));
	if (!data)
		return (0);
	data->path_split = NULL;
	data->result_split = NULL;
	cpy_env_data(env, data);
	signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		i = 0; //re intitailiser a 0
		line = readline("minishell$ ");
		if (!line)   // Ctrl-D
			break;
		add_history(line);
		data->result_split = ft_split_mod(line, ' ');
		while (data->result_split[i])
		{
			arg[i] = find_type(data->result_split[i], data);
			if (ft_strncmp(arg[i], "commande", 9)  == 0 && data->result_split[i + 1] != NULL)
			{
				i++;
				while (data->result_split[i])
				{
					if (tmp)
						free(tmp);
					tmp = find_type(data->result_split[i], data);
					printf("%s\n", tmp);
					if (ft_strncmp(tmp, "pipe", 5) == 0 || ft_strncmp(tmp, "dgreat", 7) == 0 || ft_strncmp(tmp, "great", 6) == 0 || ft_strncmp(tmp, "less", 5) == 0 || ft_strncmp(tmp, "dless", 5) == 0)
					{
						printf("OK");
						arg[i] = find_type(data->result_split[i], data);
						if (tmp)
							free(tmp);
						break;
					}
					arg[i] = ft_strdup("arg");
					i++;
				}
			}
			if (data->result_split[i] != NULL)
				i++;
		}
		i = 0;
		while (data->result_split[i])
		{
			tokens = new_token(tokens, data->result_split[i], arg[i]);
			i++;
		}
		free(line);
	}
	free_all(line, data, tokens, arg);
	return (0);
}
