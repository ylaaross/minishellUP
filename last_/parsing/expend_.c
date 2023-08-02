/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 00:23:51 by ylaaross          #+#    #+#             */
/*   Updated: 2023/08/03 00:39:52 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	exp_(t_command_d	*t)
{
	char	*c;

	c = ft_itoa(g_lob.exit_status);
	t->content = ft_strdup(c);
	free(c);
}

void	init_pipe(int *existing_pipe, int *ex_word, int *b_pipe)
{
	*existing_pipe = 1;
	*ex_word = 0;
	*b_pipe = *b_pipe - 1;
}
