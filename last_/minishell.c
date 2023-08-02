/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:43:57 by ylaaross          #+#    #+#             */
/*   Updated: 2023/08/02 00:02:33 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<readline/readline.h>
#include<readline/history.h>
#include "minishell.h"

void	count_cmd(t_pcommand_d	*p)
{
	t_pcommand_d	*tmp;
	int				i;

	tmp = p;
	i = 0;
	while (p)
	{
		i++;
		p = p->next;
	}
	while (tmp)
	{
		tmp->lenth = i;
		tmp = tmp->next;
	}
}

void	init_pointers(t_pcommand_d	**tmp, t_pcommand_d	**p)
{
	*tmp = 0;
	*p = 0;
}

void	execution_free(t_pcommand_d	*p, t_pcommand_d	*tmp)
{
	if (p && heardoc_check(p->file))
		do_heardoc(p);
	if (p)
		do_command(p);
	free_cmd_files(tmp);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->variable);
		free(env->value);
		free(env);
		env = tmp;
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_command_d		*t;
	t_pcommand_d	*p;
	t_pcommand_d	*tmp;
	int				stdin;
	int				stdout;

	(void)argc;
	(void)argv;
	var_init_env(&stdin, &stdout, &p);
	g_lob.env = __fill_env(env);
	while (1)
	{
		init_pointers(&tmp, &p);
		read_split(&t);
		if (test_cases(t))
		{
			expend_free(&t, &p);
			parse_200(t, &p, &tmp);
			free_token(t);
			count_cmd(p);
			execution_free(p, tmp);
			dup_function(stdin, stdout);
		}
	}
	return (0);
}
