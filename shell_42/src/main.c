#include "lexer/lexer.h"
#include "signal/signal.h"

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
	tmp = NULL;
	arg = NULL;
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
		if(data->result_split)
			free_tab(data->result_split);
		data->result_split = ft_split_mod(line, ' ');
		if(arg)
			free_tab(arg);
		arg = malloc(sizeof(char*) * (ft_tab_len(data->result_split) + 1));  //Malloc arg a la taille du res de split
		if(!arg)
			return(free_all(line, data, tokens, arg), 1);
		arg[ft_tab_len(data->result_split)] = NULL;
		while (data->result_split[i])
		{
			arg[i] = find_type(data->result_split[i], data);
			if (ft_strncmp(arg[i], "commande", 9)  == 0 && data->result_split[i + 1] != NULL)
			{
				i++;
				while (data->result_split[i])
				{
					if (tmp != NULL)
					{
						free(tmp);
						tmp = NULL;
					}
					tmp = find_type(data->result_split[i], data);
					printf("%s\n", tmp);
					if (ft_strncmp(tmp, "pipe", 5) == 0 || ft_strncmp(tmp, "dgreat", 7) == 0 || ft_strncmp(tmp, "great", 6) == 0 || ft_strncmp(tmp, "less", 5) == 0 || ft_strncmp(tmp, "dless", 5) == 0)
					{
						arg[i] = find_type(data->result_split[i], data);
						if (tmp != NULL)
						{
							free(tmp);
							tmp = NULL;
						}
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
