#include "get_next_line.h"

char	*realloc_and_concat(char *s1, void *buf, size_t bufsize)
{
	char	*result;
	size_t	len;
	size_t	i;

	len = (s1 ? ft_strlen(s1) : 0);
	if (!(result = (char *)malloc(len + bufsize + 1)))
		return (0);
	i = 0;
	if (s1)
	{
		while (i < len)
		{
			result[i] = s1[i];
			i++;
		}
		free(s1);
	}
	while (buf && i < bufsize + len)
	{
		result[i] = ((char *)buf)[i - len];
		i++;
	}
	result[bufsize + len] = '\0';
	return (result);
}

int		error_check(int fd, size_t bufsize)
{
	if (fd < 0 || bufsize < 1 || bufsize > MAX_INT)
		return (1);
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_memchr(const void *ptr, int c, size_t n)
{
	unsigned char	*p;
	size_t			i;

	i = 0;
	p = (unsigned char *)ptr;
	while (i < n)
	{
		if (p[i] == (unsigned char)c)
			return ((void *)&p[i]);
		i++;
	}
	return (0);
}

int		read_file(int fd, char **line, char *buf, char **rem)
{
	char	*endl;
	int		read_b;
	int		rem_bytes;

	while ((read_b = read(fd, buf, BUFFER_SIZE)))
	{
		if (read_b < 0)
			return (-1);
		if (*rem)
		{
			*line = realloc_and_concat(*line, *rem, ft_strlen(*rem));
			*rem = NULL;
		}
		if ((endl = ft_memchr(buf, '\n', read_b)))
		{
			*endl = '\0';
			*line = realloc_and_concat(*line, buf, ft_strlen(buf));
			rem_bytes = read_b - (endl - buf) - 1;
			*rem = realloc_and_concat(*rem, endl + 1, rem_bytes);
			return (1);
		}
		else
			*line = realloc_and_concat(*line, buf, read_b);
	}
	return (0);
}