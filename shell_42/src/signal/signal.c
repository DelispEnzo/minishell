/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelispo <edelispo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:00:54 by enzo              #+#    #+#             */
/*   Updated: 2026/01/30 12:08:58 by edelispo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"

int g_status = 0;


void handle_sigint(int sig)
{
    (void)sig;
    g_status = 130; // Code standard pour SIGINT
    write(1, "\n", 1);
	rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

