/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:12:38 by asaber            #+#    #+#             */
/*   Updated: 2023/07/17 22:11:10 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
#include "../minishell.h"

char	*get_next_line(int fd);
int		t_sln(char *str);
int		t_strchr(char *s, int c);
char	*t_strjoin(char *str1, char *str2);
char	*t_substr(char *s, int start, int len);
char	*t_strdup(char *s1);
char	*t_calloc(int count, int size);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

#endif