#include "get_next_line.h"
#include <fcntl.h>

int		get_next_line(int fd, char **line)
{
	static char		*remainder;
	char			*buf;
	char			*endl;
	int				status;

	if (error_check(fd, BUFFER_SIZE) || !(buf = (char *)malloc(BUFFER_SIZE)))
		return (-1);
	*line = NULL;
	if (remainder && (endl = ft_memchr(remainder, '\n', ft_strlen(remainder))))
	{
		*endl = '\0';
		*line = realloc_and_concat(*line, remainder, ft_strlen(remainder));
		remainder = endl + 1;
		return (1);
	}
	status = read_file(fd, line, buf, &remainder);
	free(buf);
	if (status == 0)
		free(*line);
	return (status);
}

int main(int ac, char**av)
{

	int fd = open(av[1],O_RDONLY);
	char **line = (char **)malloc(sizeof(char *));
	*line = NULL;
	while (get_next_line(fd, line))
		printf("<%s>\n", *line);
}
