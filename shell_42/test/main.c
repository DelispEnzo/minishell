#include "token.h"

struct token *get_last_token(struct token* tokens)
{
    struct token *element;

    element = tokens;
    if(!element)
        return(NULL);
    while(element->next != NULL)
    {
        element = element->next;
    }
    return(element);
}

struct token *new_token(struct token* tokens, char *value, char* type)
{
    struct token *next;
    struct token *last_element;

    next = malloc(sizeof(struct token));
    if(!next)
        return(NULL);
    next->value = ft_strdup(value);
    if(!next->value)
    {
        free(next);
        return(NULL);
    }
    next->type = ft_strdup(type);
    if(!next->type)
    {
        free(next->value);
        free(next);
        return(NULL);
    }
    next->next = NULL;
    last_element = get_last_token(tokens);
	printf("type : %s\n", next->type);
	printf("token : %s\n", next->value);
    if(!last_element)
        return(next);
    last_element->next = next;
    return(tokens);
}

void cpy_env_data(char **env, struct data *data)
{
	int i;
	int x;
	int size;


	i = 0;
	size = 0;
	x = 0;
	while (env[size])
		size++;
	data->env = malloc(sizeof(char *) * size);
	if (!data->env)
		return ;
	data->env[size] = NULL;
	while (env[i])
	{
		x = 0;
		data->env[i] = malloc(sizeof(char) * ft_strlen(env[i]));
		if (!data->env[i])
			printf("bien tout free"); // a ne pas oublie de modifier
		while (env[i][x])
		{
			data->env[i][x] = env[i][x];
			x++;
		}
		i++;
	}
}

int check_acces(char *str, struct data *data) // verifie si la commande existe ou non
{
	int i;
	char *path;
	char	*av2;
	char	*valid_path;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(data->env[i]);
			if (!path)
				return (0);
		}
		i++;
	}
	data->path_split = ft_split(path, ':');
	i = 0;
	av2 = ft_strjoin("/", str);
	valid_path = NULL;
	while (data->path_split[i])
	{
		valid_path = ft_strjoin(data->path_split[i], av2);
		if (access(valid_path, X_OK) == 0)
		{
			free(av2);
			free(valid_path);
			return (1);
			break ;
		}
		i++;
		free(valid_path);
	}
	free(av2);
	return (0);
}

char *find_type(char *str, struct data *data) // cherche les type
{
	char *type;
	int i;

	i = 0;
	printf("cmp = %d\n", ft_strncmp(str, "echo", 5));
	type = malloc(sizeof(char) * 10);
	if (!type)
		return (NULL);
	else if (ft_strncmp(str, "echo", 5) == 0 || ft_strncmp(str, "cd", 2) == 0 || ft_strncmp(str, "pwd", 3) == 0  || ft_strncmp(str, "export", 7) == 0  || ft_strncmp(str, "unset", 6) == 0  || ft_strncmp(str, "env", 4) == 0  || ft_strncmp(str, "exit", 5) == 0 )
	{
		type = "commande";
		return (type);
	}
	else if (ft_strncmp(str, "|", 2) == 0)
	{
		type = "pipe";
		return (type);
	}
	else if (ft_strncmp(str, ">>", 3) == 0)
	{
		type = "dgreat";
		return(type);
	}
	else if (ft_strncmp(str, ">", 2) == 0)
	{
		type = "great";
		return(type);
	}
	else if (ft_strncmp(str, "<<", 3) == 0)
	{
		type = "dless";
		return(type);
	}
	else if (ft_strncmp(str, "<", 2) == 0)
	{
		type = "less";
		return(type);
	}
	else if (check_acces(str, data) == 1)
	{
		type = "commade";
		return (type);
	}
	else
	{
		type = "mot";
		return (type);
	}
	return (NULL);
}


int free_all(char *line, struct data *data, struct token *tokens) // free
{
	int i;

	i = 0;
	free(line);
	while (data->env[i])
	{
		free(data->env[i]);
		i++;
	}
	i = 0;
	while (data->path_split)
	{
		free(data->path_split[i]);
		i++;
	}
	i = 0;
	while (data->result_split)
	{
		free(data->result_split[i]);
		i++;
	}

	destroy_tokens(tokens);
}
int main(int ac, char **av, char **env)
{
	struct data *data;
	struct token *tokens;
	char *line;
	int i;

	i = 0;
	tokens = malloc(sizeof(struct token));
	if (!tokens)
		return (0);
	data = malloc(sizeof(struct data));
	if (!data)
		return (0);
	data->path_split = NULL;
	cpy_env_data(env, data);
	while (1)
	{
		line = readline("minishell$ ");
        if (!line)   // Ctrl-D
            break;

		data->result_split = ft_split(line, ' ');
		while (data->result_split[i])
		{
			tokens = new_token(tokens, data->result_split[i], find_type(data->result_split[i], data));
			i++;
		}
	}
}
