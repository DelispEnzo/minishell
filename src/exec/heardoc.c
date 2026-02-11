/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:04:21 by enzo              #+#    #+#             */
/*   Updated: 2026/02/10 16:24:20 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	gestion_heredoc(char *delimiteur, int expand, struct data *data)
{
	int		fd;
	char	*ligne;

	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	while (1)
	{
		ligne = readline("> ");
		if (!ligne)
			break ;
		if (ft_strcmp(ligne, delimiteur) == 0)
		{
			free(ligne);
			break ;
		}
		if (expand == 1)
			ligne = chiant(ligne, data);
		write(fd, ligne, strlen(ligne));
		write(fd, "\n", 1);
		free(ligne);
	}
	close(fd);
	fd = open(".heredoc_tmp", O_RDONLY);
	return (unlink(".heredoc_tmp"), fd);
}
