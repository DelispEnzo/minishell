/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elquesne <elquesne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:59:49 by enzo              #+#    #+#             */
/*   Updated: 2026/01/26 13:23:16 by elquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
#define SIGNAL_H

#include "../tokens/token.h"
#include "../lexer/lexer.h"
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

extern int g_status;


void handle_sigint(int sig);

#endif // SIGNAL_H
