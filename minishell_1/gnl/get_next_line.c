/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 13:33:08 by asaber            #+#    #+#             */
/*   Updated: 2023/07/17 22:11:03 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*t_strdup(char *str)
{
	char	*pt;
	int		ln;
	int		i;

	i = 0;
	ln = t_sln(str);
	pt = (char *)malloc(ln + 1);
	while (ln >= i)
	{
		pt[i] = str[i];
		i++;
	}
	return (pt);
}

char	*t_readnstock(int fd, char *s_var)
{
	char	*add;
	int		i;

	if (!s_var)
		s_var = t_calloc(1, 1);
	add = t_calloc(BUFFER_SIZE + 1, 1);
	i = 1;
	while (i > 0)
	{
		i = read(fd, add, BUFFER_SIZE);
		if ((s_var[0] == 0 && add[0] == 0) || i < 0)
		{
			free(add);
			free(s_var);
			return (0);
		}
		add[i] = '\0';
		s_var = t_strjoin(s_var, add);
		if (t_strchr(add, '\n') >= 0)
			break ;
	}
	free(add);
	return (s_var);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE == 0)
		return (0);
	stock = t_readnstock(fd, stock);
	if (!stock)
	{
		free(stock);
		return (NULL);
	}
	if (t_strchr(stock, '\n') >= 0)
	{
		line = t_substr(stock, 0, t_strchr(stock, '\n'));
		tmp = t_substr(stock, t_strchr(stock, '\n') + 1, t_sln(stock));
		free(stock);
		stock = tmp;
		return (line);
	}
	line = t_strdup(stock);
	free(stock);
	stock = NULL;
	return (line);
}
