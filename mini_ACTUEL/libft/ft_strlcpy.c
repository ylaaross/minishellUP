/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:44:01 by asaber            #+#    #+#             */
/*   Updated: 2022/10/25 11:26:23 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *s, size_t dstsize)
{
	size_t	sln;

	sln = ft_strlen((char *)s);
	if (sln + 1 < dstsize)
	{
		ft_memcpy(dst, s, sln);
		dst[sln] = '\0';
	}
	else if (dstsize != 0)
	{
		ft_memcpy(dst, s, dstsize);
		dst[dstsize - 1] = '\0';
	}
	return (sln);
}
