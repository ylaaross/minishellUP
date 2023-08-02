/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:36:29 by asaber            #+#    #+#             */
/*   Updated: 2023/08/01 17:01:07 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	forc_check(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_echo(t_pcommand_d *t)
{
	int	i;
	int	n;
	int	j;

	i = 1;
	n = 0;
	j = 0;
	while (t->command[i] && ft_strncmp(t->command[i], "-n", 2) == 0)
	{
		if (forc_check(t->command[i]))
			break ;
		n = 1;
		i++;
	}
	while (t->command[i])
	{
		printf("%s", t->command[i]);
		if (t->command[i + 1])
			printf(" ");
		i++;
	}
	if (n == 0)
		printf("\n");
}
