/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylaaross <ylaaross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:53:24 by ylaaross          #+#    #+#             */
/*   Updated: 2023/06/10 12:47:05 by ylaaross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<stdlib.h>

int	ft_strlenm(char const *s, int index, char c)
{
	int	i;

	i = 0;
	while (s[index] != c && s[index] && s[index] != '"')
	{
		i++;
		index++;
	}
	return (i);
}

char	*cp(char const *s, char c, int *index, int ft_strlenm)
{
	char	*p;
	int		i;

	p = 0;
	i = 0;
	p = (char *)malloc((size_t)ft_strlenm * sizeof(char) + 1);
	if (!p)
		return (0);
	else
	{
		while (s[*index] && s[*index] != c && s[*index] != '"')
		{
			p[i] = s[*index];
			i++;
			*index = *index + 1;
		}
		p[i] = 0;
	}
	return (p);
}

void	findwords(char const *s, int *index, char c)
{
	while (s[*index] && s[*index] == c && s[*index] != '"')
			*index = *index + 1;
}

char	**ft_split(char const *s, char c)
{
	int		index;
	char	**p;
	int		i;
	int		wc;

	i = 0;
	index = 0;
	if (!s)
		return (0);
	wc = count_words(s, c);
	p = (char **)malloc((wc + 1) * sizeof(char *));
	if (!p)
		return (0);
	while (i < wc)
	{
		findwords(s, &index, c);
		p[i] = cp(s, c, &index, ft_strlenm(s, index, c));
		i++;
	}
	p[i] = 0;
	return (p);
}
