/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 19:52:15 by youkhart          #+#    #+#             */
/*   Updated: 2019/10/25 00:47:58 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_memchr(char	*b, char c, size_t bufsize)
{
	size_t	i;

	i = 0;
	while (i < bufsize)
	{
		if (b[i] == c)
			return (&b[i]);	
		i++;
	}
	return (0);
}
char	*realloc_and_concat(char *s, char *buf, size_t bufsize)
{
	size_t	i;
	size_t	len;
	char	*res;
	
	len = (s ? ft_strlen(s) : 0);
	if(!(res = (char *)malloc(sizeof(char) * (len + bufsize + 1))))
		return (0);
	i = 0;
	if (s)
	{
		while (s[i])
		{
			res[i] = s[i];
			i++;
		}
		free (s);
	}
	while (i < bufsize + len)
	{
		res[i] = buf[i - len];
		i++;
	}
	res[len + bufsize] = '\0';
	return (res);
}
