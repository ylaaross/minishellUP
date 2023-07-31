/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 18:13:10 by ylaaross          #+#    #+#             */
/*   Updated: 2023/08/01 00:05:03 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<readline/readline.h>
#include<readline/history.h>
#include "../minishell.h"

void	skip_files(t_command_d **t)
{
	*t = (*t)->next;
	while (*t && ((*t)->token == SPACE || (*t)->token == TAB))
		(*t) = (*t)->next;
}

void	join_parse_next(t_command_d **t, int *state, char **s)
{
	if ((*t)->token == QUOTES || (*t)->token == SQUOTES)
		*state = 1;
	if (content_file_parse((*t)))
	*s = ft_strjoin_parse(*s, (*t)->content);
	next(t);
}

void	kk(t_command_d **t, t_pcommand_d *p, int *i)
{
	if (*t && !(test2((*t)) && (*t)->state == GENERALE)
		&& !((*t)->token == SPACE && (*t)->state == GENERALE)
		&& !((*t)->token == TAB && (*t)->state == GENERALE)
		&& !((*t)->token == PIPE && (*t)->state == GENERALE))
		inside_parse(t, p, i);
}

void	state_token(t_command_d **t, int *state, int *token)
{
	*state = 0;
	*token = detect_token(*t);
	skip_files(t);
}

void	pipe_next(t_command_d **t, t_pcommand_d **p, int *i)
{
	pipe_(*t, p, i);
	next(t);
}
