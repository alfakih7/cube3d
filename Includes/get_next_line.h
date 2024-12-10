
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
void	ft_bzero(void *s, size_t n);
char	*ft_strdup(const char *s);

#endif