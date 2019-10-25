/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:02:55 by youkhart          #+#    #+#             */
/*   Updated: 2019/10/24 23:13:33 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>

size_t	ft_strlen(char *str);
char	*ft_memchr(char *b, char c, size_t bufsize);
char	*realloc_and_concat(char *s, char *buf, size_t bufsize);
#endif
