#include "exec.h"

struct commande	*create_commande_list(struct token *tokens);

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
	return (NULL);
}

int	execution(struct commande *cmd, struct token *tokens)
{
	(void)tokens;
	if (!cmd->value)
		return (0);
	if (strcmp(cmd->value, "echo") == 0)
	{
		echo(cmd->argv);
		return (1);
	}
	return (0);
}

int	parser(struct token *tokens, struct data *data)
{
	struct commande	*commande;
	int				fd[2]; // fd[0] = clavier // fd[1] = ecran
	int				prev;
	pid_t			pid;
	char			*valid_path;

	prev = -1;
	commande = create_commande_list(tokens);
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
				fd_out = open(commande->outfile, flag);
				if (fd_out == -1)
				{
					perror(commande->outfile);
					exit(1);
				}
				dup2(fd_out, STDOUT_FILENO);
				close(fd_out);
			}
			if (execution(commande, tokens) == 0)
			{
				valid_path = check_path(commande->value, data);
				if (valid_path == NULL)
					return (0);
				execve(valid_path, commande->argv, data->env);
			}
			exit(1);
		}
		else
		{
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
