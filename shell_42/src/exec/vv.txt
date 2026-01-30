#include "exec.h"


char *check_path(char *str, struct data *data) // verifie le chemin de la commande
{
	int i;
	char *path;
	char	*av2;
	char	*valid_path;

	i = 0;
	path = NULL;
	while (data->env[i] != NULL)
	{
		if (ft_strncmp(data->env[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(data->env[i] + 5);
			if (!path)
				return (0);
			break;
		}
		i++;
	}
	if (!path)
        return (NULL);
	if(data->path_split)
		free_tab (data->path_split);
	data->path_split = ft_split(path, ':');
	if(!data->path_split)
	{
		free(path);
		return(NULL);
	}
	free(path);
	i = 0;
	av2 = ft_strjoin("/", str);
	valid_path = NULL;
	while (data->path_split[i])
	{
		valid_path = ft_strjoin(data->path_split[i], av2);
		if (access(valid_path, X_OK) == 0)
		{
			free(av2);
			return (valid_path);
		}
		i++;
		free(valid_path);
	}
	free(av2);
	return (NULL);
}

int	execution(struct commandes *cmd, struct token *tokens, struct data *data)
{
	int i = 0;
	(void)tokens;
	if (!cmd->value)
		return (0);
	if (strcmp(cmd->value, "echo") == 0)
	{
		echo(cmd->argv);
		return (1);
	}
	else if (strcmp(cmd->value, "pwd") == 0)
	{
		i = ft_pwd();
		return (1);
	}
	else if (strcmp(cmd->value, "cd") == 0)
	{
		return (1);
	}
	else if (strcmp(cmd->value, "export") == 0)
	{
		return (1);
	}
	else if (strcmp(cmd->value, "env") == 0)
	{
		i = env(data);
		return (1);
	}
	return (0);
}

void free_machin_truc(struct token *tokens, struct data *data, struct commandes *cmd)
{
    if (cmd)
        free_commande(cmd);

    if (tokens)
        destroy_tokens(tokens);
    if (data)
    {
        if (data->result_split)
            free_tab(data->result_split);
        if (data->path_split)
            free_tab(data->path_split);
        if (data->export_tab)
            free_tab(data->export_tab);
        if (data->env)
            free_tab(data->env);
        free(data);
    }
}
int	exec(struct token *tokens, struct data *data, struct commandes *cmd)
{
	struct commandes	*commande;
	int				fd[2]; // fd[0] = clavier // fd[1] = ecran
	int				prev;
	pid_t			pid;
	char			*valid_path;

	prev = -1;
	commande = cmd;
	valid_path = NULL;
	while (commande)
	{
		if (commande->next)
		{
			if (pipe(fd) == -1)
				exit(1);
		}

		pid = fork();
		if (pid == 0)
		{
			if (prev != -1)
			{
				dup2(prev, STDIN_FILENO);
				close(prev); // Je branche mon clavier (0) sur le tuyau d'avant
			}
			if (commande->next)
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			if (commande->heredoc_mode == 1)
			{
				int fd_heredoc = gestion_heredoc(commande->limiter);
				dup2(fd_heredoc, STDIN_FILENO);
				close(fd_heredoc);
			}
			else if (commande->infile != NULL) // <
			{
				int fd_in;

				fd_in = open(commande->infile, O_RDONLY);
				if (fd_in == -1)
				{
					perror(commande->infile);
					free_machin_truc(tokens, data, cmd);
					exit(1);
				}
				dup2(fd_in, STDIN_FILENO);
				close(fd_in);
			}
			else if (commande->outfile != NULL) // > || >>
			{
				int fd_out;
				int flag;

				if (commande->append_mode == 1) //  >>
					flag = O_WRONLY | O_CREAT | O_APPEND;
				else // >
					flag = O_WRONLY | O_CREAT | O_TRUNC;
				fd_out = open(commande->outfile, flag, 0644);
				if (fd_out == -1)
				{
					perror(commande->outfile);
					free_machin_truc(tokens, data, cmd);
					exit(1);
				}
				dup2(fd_out, STDOUT_FILENO);
				close(fd_out);
			}
			if (execution(commande, tokens, data) == 0)
			{
				valid_path = check_path(commande->value, data);
				if (valid_path == NULL)
				{
					write(2, "minishell: command not found: ", 30);
					write(2, commande->value, ft_strlen(commande->value));
					write(2, "\n", 1);
					free(valid_path);
					free_machin_truc(tokens, data, cmd);
					exit(127);
				}
				execve(valid_path, commande->argv, data->env);
				free(valid_path);
				perror("execve");
				free_machin_truc(tokens, data, cmd);
				exit(126);
			}
			free_machin_truc(tokens, data, cmd);
			exit(0);
		}
		else
		{
			if (strcmp(cmd->value, "cd") == 0)
			{
				ft_cd(cmd->argv, data);
			}
			else if (strcmp(cmd->value, "export") == 0)
			{
				ft_export(tokens, data);
			}
			if (prev != -1) // si on a fini de lire dans le fd on le close
				close(prev);
			if (commande->next)
				// si il y a une commande apres on ferme le fd[1] et on met sur entre
			{
				close(fd[1]);
				prev = fd[0];
			}
			commande = commande->next; // maillons suivant
		}
	}
	while (wait(NULL) > 0)
	{}
	return (0);
}
