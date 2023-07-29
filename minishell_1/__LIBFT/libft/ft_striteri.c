/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaber <asaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 08:51:58 by asaber            #+#    #+#             */
/*   Updated: 2022/10/25 11:26:03 by asaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

/*void	ff(unsigned int i, char *ptr)
{
	ptr[i] += 1;
}*/

char	*ft_stcheck(char *s, void (*f)(unsigned int, char*))
{
	if (!s || !f)
		return (0);
	return (s);
}

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;
	size_t	len;

	if (!s)
		return ;
	ft_stcheck(s, f);
	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		f(i, &s[i]);
		i++;
	}
}
