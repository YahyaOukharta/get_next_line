#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"

#define magic_number 8384744  //a buffersize larger than this will cause segfault

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
	static char *remainder;
	char buf[BUFFER_SIZE];
	char *endl;
	int		remaining_bytes;
	int		read_b;

	*line = NULL;
/*	if (!remainder)
	{
		char *str = "abcdef\n123456\n123\n!@#$\n\n123\n\0";
		remainder = realloc_and_concat(remainder, str, ft_strlen(str));
	}
*/
//printf("remainder = <%s>\n", remainder);	
	if (remainder && (endl = ft_memchr(remainder, '\n', ft_strlen(remainder))))
	{
		*endl = '\0';
		*line = realloc_and_concat(*line, remainder, ft_strlen(remainder));
		//printf("iiiline = %s \n",*line);
		remainder = endl + 1;
		return (1);
	}
	while((read_b = read(fd, buf, BUFFER_SIZE)))
	{
		//printf("started reading, buf=\n");
		//print_buf(buf, read_b);
		endl = ft_memchr(buf , '\n', read_b);
		if (remainder)
		{	
			//printf("1st remainder = <%s>\n",remainder);
			*line = realloc_and_concat(*line, remainder, ft_strlen(remainder));
			remainder = NULL;
		}
		if(endl)
		{
			//printf("buf = \n");
			*endl = '\0';
			*line = realloc_and_concat(*line, buf, ft_strlen(buf));
			
			//printf("line = %s\n", *line);
		
			// put \0 at end of remainder, ofcourse must duplicate it first 
			// because buf is emptied on each iteration of the function

			remaining_bytes = read_b - (endl - buf) - 1;
			remainder = realloc_and_concat(remainder, endl + 1, remaining_bytes);
			return (1);
		}
		else
		{
			*line = realloc_and_concat(*line, buf, read_b);
		}
	}

	return  (0);
}

int main(int argc, char **argv)
{
	char **line = (char **)malloc(sizeof(char *));
	int fd = open("f.txt", O_RDONLY);	
	if(fd)
		printf("opened file\n");
	else return 0;

	while(get_next_line(fd,line))
	{
		printf("<%s>\n",*line);
	}
}
