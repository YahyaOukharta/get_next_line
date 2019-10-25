/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 19:42:54 by youkhart          #+#    #+#             */
/*   Updated: 2019/10/25 02:22:14 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
int	get_next_line(int fd, char **line)
{
	static char	*remainder;
	static int state;
	char		*buf;
	char		*endl;
	ssize_t		read_b;
	
	*line = NULL;
	if (remainder
			&& ((endl = ft_memchr(remainder, '\n', ft_strlen(remainder)))))
	{
		if (state)
			endl = remainder + ft_strlen(remainder);
		*endl = '\0';
		*line = realloc_and_concat(*line, remainder, ft_strlen(remainder));
		remainder = endl + 1; //must free and realloc
		return (1);
	}
	if(!(buf = (char *)calloc(BUFFER_SIZE, sizeof(char))))
		return (-1);
	
	while ((read_b = read(fd, buf, BUFFER_SIZE)))
	{
		if (remainder)
		{
			*line = realloc_and_concat(*line, remainder, ft_strlen(remainder));
		//	free(remainder);
			remainder = NULL;
		}
		if (*line && read_b < BUFFER_SIZE && !ft_memchr(buf, '\n', read_b))
		{
			buf[read_b] = '\n';
			read_b++;
		}
		if ((endl = ft_memchr(buf, '\n', read_b)))
		{
			*endl = '\0';
			*line = realloc_and_concat(*line, buf, ft_strlen(buf));
			remainder = realloc_and_concat(remainder, endl + 1, read_b - (endl - buf) - 1);
			free(buf);
			return (1);	
		}
		else
			*line = realloc_and_concat(*line, buf, read_b);
	}
	if (*line == NULL)
		return (0);
	if (!state)
	{
		state = 1;
		return (state);	
	}
	return(0);
}

int main(int argc, char **argv)
{
	char 	*line;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
		printf("<%s>\n",line);
}
