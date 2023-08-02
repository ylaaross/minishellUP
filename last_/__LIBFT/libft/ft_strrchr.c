/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:12:03 by asaber            #+#    #+#             */
/*   Updated: 2022/10/24 13:11:07 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	lns;

	lns = ft_strlen(s);
	while ((unsigned char)s[lns] != (unsigned char)c && lns != 0)
		lns--;
	if ((unsigned char)s[lns] == (unsigned char)c)
		return ((char *)&s[lns]);
	return (0);
}
