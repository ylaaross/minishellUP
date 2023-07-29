/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:37:33 by asaber            #+#    #+#             */
/*   Updated: 2022/10/25 11:27:32 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*finall_str;
	size_t	ln;

	if (!set)
		return ((char *)s1);
	if (!s1)
		return (0);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	ln = ft_strlen(s1);
	while (ln && s1[ln - 1] && ft_strchr(set, s1[ln - 1]))
		ln--;
	finall_str = malloc((ln + 1) * sizeof(char));
	if (!finall_str)
		return (0);
	ft_memcpy(finall_str, s1, ln);
	finall_str[ln] = '\0';
	return (finall_str);
}
