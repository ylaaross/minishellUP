/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:23:50 by asaber            #+#    #+#             */
/*   Updated: 2022/10/25 11:27:18 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

char	*ft_strnstr(const char *src, const char *tosrch, size_t ln)
{
	size_t	len_to;

	if (!src && ln == 0)
		return (0);
	len_to = ft_strlen(tosrch);
	if (len_to == 0)
		return ((char *)src);
	while (*src && ln >= len_to)
	{
		if (*tosrch == *src)
			if (ft_strncmp(src, tosrch, len_to) == 0)
				return ((char *)src);
		src++;
		ln--;
	}
	return (0);
}
