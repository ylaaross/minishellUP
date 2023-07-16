/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 23:07:21 by asaber            #+#    #+#             */
/*   Updated: 2023/07/13 15:56:52 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirection(t_pcommand_d *t)
{
	int		fd;
	t_file	*file;

	file = t->file;
	while (file)
	{
		if (file->type == 8)
			fd = open(file->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (file->type == 14)
			fd = open(file->file_name, O_RDONLY);
		if (fd == -1)
		{
			printf("minishell: %s: %s\n", file->file_name, strerror(errno));
			return (fd);
		}
		file = file->next;
	}
	return (fd);
}
