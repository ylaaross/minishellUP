/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:15:33 by asaber            #+#    #+#             */
/*   Updated: 2022/10/25 11:27:39 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr_s;
	char	*ptralloc;
	size_t	i;

	i = 0;
	ptr_s = (char *) s + start;
	if (!s || start > ft_strlen(s))
		return (ft_strdup(""));
	if (start < ft_strlen(s))
	{
		ptralloc = (char *) malloc(len + 1 * sizeof(char));
		if (ptralloc == 0)
			return (0);
		ft_strlcpy(ptralloc, ptr_s, len + 1);
		return (ptralloc);
	}
	return (NULL);
}
