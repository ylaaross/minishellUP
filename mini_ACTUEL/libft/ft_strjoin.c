/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 22:13:48 by asaber            #+#    #+#             */
/*   Updated: 2022/11/06 02:06:10 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*allstr;
	size_t	lens1;
	size_t	lens2;

	if (!s1 || !s2)
		return (0);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	allstr = malloc((lens1 + lens2 + 1) * sizeof(char));
	if (allstr == 0)
		return (0);
	ft_memcpy(allstr, s1, lens1);
	ft_memcpy(allstr + lens1, s2, lens2);
	*(allstr + lens1 + lens2) = '\0';
	return (allstr);
}
