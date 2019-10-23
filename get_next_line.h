#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define MAX_INT 2147483647
# include "get_next_line.h"
# include <stdlib.h>
# include <unistd.h>

int		error_check(int fd, size_t bufsize);
size_t	ft_strlen(const char *str);
void	*ft_memchr(const void *ptr, int c, size_t n);
char	*realloc_and_concat(char *s1, void *buf, size_t bufsize);
int		read_file(int fd, char **line,char *buf, char **remainder);
int		get_next_line(int fd, char **line);
#endif
