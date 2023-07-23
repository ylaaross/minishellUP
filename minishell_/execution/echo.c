/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:36:29 by asaber            #+#    #+#             */
/*   Updated: 2023/07/22 20:27:37 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_pcommand_d *t)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (redirect(t) == -1)
		return ;
	while (t->command[i] && ft_strncmp(t->command[i], "-n", ft_strlen(t->command[i])) == 0)
	{
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