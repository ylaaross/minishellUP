/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 20:49:56 by asaber            #+#    #+#             */
/*   Updated: 2023/07/31 16:47:31 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	__pwd(t_pcommand_d *cmd)
{
	char	*pwd;

	if (redirect(cmd) == -1)
		return ;
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	g_lob.exit_status = 0;
	(void)cmd;
}
