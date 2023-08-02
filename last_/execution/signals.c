/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:59:40 by asaber            #+#    #+#             */
/*   Updated: 2023/08/02 17:53:16 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write (2, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		g_lob.exit_status = 1;
	}
}

void	signals(void)
{
	signal (SIGINT, sig_handler);
	signal (SIGQUIT, SIG_IGN);
}

void	def_signals(void)
{
	signal (SIGINT, SIG_DFL);
	signal (SIGQUIT, SIG_DFL);
}
