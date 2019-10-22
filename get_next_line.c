#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"

#define MAX_INT 2147483647

void	print_buf(void *buf, int size)
{
	int i = 0;
	while(i < size)
	{
		write(1,&buf[i],1);
		i++;
	}
	printf("\n\n");
}

char	*realloc_and_concat(char *s1, void *buf, size_t bufsize)
{
	char	*result;
	size_t	len;

	len = (s1 ? ft_strlen(s1) : 0);
	result = (char *)malloc(len + bufsize + 1);
	if (!result)
		return(0);
	if (s1)
	{
		ft_memcpy(result, (void *)s1, len);
		free(s1);
	}
	ft_memcpy(result + len, buf, bufsize);
	result[bufsize + len] = '\0';
	return (result);
}

int		get_next_line(int fd, char **line)
{
	static char		*remainder;
	char			*buf; //[BUFFER_SIZE];
	char 			*endl;
	int				remaining_bytes;
	int				read_b;
	// allocating on heap cuz stack is very limited
	if (fd < 0 || BUFFER_SIZE < 1 || BUFFER_SIZE > MAX_INT || !(buf = (char *)malloc(BUFFER_SIZE)))
		return (-1);
	*line = NULL;

	if (remainder && (endl = ft_memchr(remainder, '\n', ft_strlen(remainder))))
	{
		*endl = '\0';
		*line = realloc_and_concat(*line, remainder, ft_strlen(remainder));
		remainder = endl + 1;
		return (1);
	}
	while((read_b = read(fd, buf, BUFFER_SIZE)))
	{
		if (read_b < 0)
			return (-1);
		endl = ft_memchr(buf , '\n', read_b);
		if (remainder)
		{	
			*line = realloc_and_concat(*line, remainder, ft_strlen(remainder));
			remainder = NULL;
		}
		if(endl)
		{
			*endl = '\0';
			*line = realloc_and_concat(*line, buf, ft_strlen(buf));
			remaining_bytes = read_b - (endl - buf) - 1;
			remainder = realloc_and_concat(remainder, endl + 1, remaining_bytes);
			free(buf);
			return (1);
		}
		else
			*line = realloc_and_concat(*line, buf, read_b);
	}
	free(buf);
	free(*line);
	return (0);
}

int main(int argc, char **argv)
{
	char **line = (char **)malloc(sizeof(char *));
	int fd = 1;//open(argv[1], O_RDONLY );	
	if(fd > 0)
		printf("opened file\n");
	else 
		return 0;

	while(get_next_line(fd,line) > 0)
	{
		printf("<%s>\n",*line);
	}
}
