/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell9.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 22:19:37 by ylaaross          #+#    #+#             */
/*   Updated: 2023/08/01 00:06:27 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	test_cases(t_command_d	*t)
{
	if (detect_quotes2(t) && herdock_redirect_test(t, REDIRECT_IN)
		&& herdock_redirect_test(t, REDIRECT)
		&& herdock_redirect_test(t, REDIRECT_IN)
		&& herdock_redirect_test(t, APPEND)
		&& herdock_redirect_test(t, HERDOCK) && pipe_red_test(t, PIPE))
		return (1);
	free_token(t);
	write(2, "minishell: syntax error\n", 24);
	return (0);
}

void	var_init_env(int *stdin, int *stdout, t_pcommand_d	**p)
{
	*p = 0;
	*stdin = dup(STDIN_FILENO);
	*stdout = dup(STDOUT_FILENO);
}

void	read_split(t_command_d	**t)
{
	char	*read;

	*t = 0;
	read = readline("minishell> ");
	if (!read)
		exit(g_lob.exit_status);
	add_history(read);
	split_parse(read, t);
	detect_state(*t);
}

void	expend_free(t_command_d **t, t_pcommand_d	**p)
{
	*p = 0;
	*t = expend(*t);
	expend_exit(*t);
}

void	dup_function(int stdin, int stdout)
{
	dup2(stdin, STDIN_FILENO);
	dup2(stdout, STDOUT_FILENO);
}
