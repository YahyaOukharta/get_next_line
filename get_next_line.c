/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:46:14 by youkhart          #+#    #+#             */
/*   Updated: 2019/10/27 16:22:57 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int		get_next_line(int fd, char **line)
{
	static char		*remainder;
	char			*buf;
	char			*endl;
	int				status;
	char 			*tmp;

	if (error_check(fd, BUFFER_SIZE) || !(buf = (char *)malloc(BUFFER_SIZE)))
		return (-1);
	free((*line ? *line : NULL));
	*line = NULL;
	if (remainder)
	{
	/*	if ((endl = ft_memchr(remainder, '\n', ft_strlen(remainder))))
		{
			*endl = '\0';
			*line = realloc_and_concat(*line, remainder, ft_strlen(remainder));
			tmp = realloc_and_concat(NULL, endl + 1, ft_strlen(endl + 1));
			free(remainder);
			remainder = tmp;
			free(buf);
			return (1);
		}
		else
		{
			*line = realloc_and_concat(*line, remainder, ft_strlen(remainder));
			free(remainder);
			remainder = NULL;
		}
	*/
		endl = ft_memchr(remainder, '\n', ft_strlen(remainder));
		if (endl)
			*endl = '\0'; // if \n occurs
		*line = realloc_and_concat(*line, remainder, ft_strlen(remainder));
		tmp = (endl ? realloc_and_concat(NULL, endl + 1, ft_strlen(endl + 1)) : NULL);
		free(remainder);
		remainder = tmp;
		if (endl)
		{
			free(buf);
			return(1);
		}
	}
	status = read_file(fd, line, buf, &remainder);
	free(buf);
	return (status);
}

int main(int argc, char **argv)
{
	int fd;
	char *line;

	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
			printf("<%s>\n",line);
	}			
}
