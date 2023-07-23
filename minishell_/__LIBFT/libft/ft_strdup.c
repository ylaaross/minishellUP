/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:02:44 by asaber            #+#    #+#             */
/*   Updated: 2022/11/23 16:20:03 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*pt;
	int		ln;
	int		i;

	i = 0;
	ln = ft_strlen(s1);
	pt = (char *)malloc(ln + 1);
	if (!pt)
		return (0);
	while (ln >= i)
	{
		pt[i] = s1[i];
		i++;
	}
	return (pt);
}
