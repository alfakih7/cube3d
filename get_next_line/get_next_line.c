#include <stdio.h>
#include "../Includes/get_next_line.h"

static void	ft_free(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

static char	*ft_remaining(char **arr)
{
	char	*line;
	char	*temp;
	char	*newline;

	line = NULL;
	newline = ft_strchr(*arr, '\n');
	if (newline)
	{
		*newline = '\0';
		line = ft_strjoin(*arr, "\0");
		if (*(newline + 1))
		{
			temp = ft_strdup(newline + 1);
			if (!temp)
				return (ft_free(&line), ft_free(arr), NULL);
			ft_free(arr);
			*arr = ft_strdup(temp);
			return (ft_free(&temp), line);
		}
		return (ft_free(arr), line);
	}
	line = ft_strdup(*arr);
	return (ft_free(arr), line);
}

static char	*ft_dupjoin(char *arr, char *buff)
{
	char	*join;

	if (!arr)
	{
		arr = ft_strdup(buff);
		return (arr);
	}
	else
	{
		join = ft_strjoin(arr, buff);
		return (ft_free(&arr), join);
	}
}

static char	*ft_handleline(char **arr, int fd)
{
	char	*buff;
	ssize_t	counter;

	counter = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (counter > 0)
	{
		counter = read(fd, buff, BUFFER_SIZE);
		if (counter < 0)
			return (ft_free(arr), free(buff), NULL);
		buff[counter] = '\0';
		if (counter > 0)
			*arr = ft_dupjoin(*arr, buff);
		if (counter == 0 || ft_strchr(buff, '\n'))
			break ;
	}
	if (*arr)
		return (free(buff), ft_remaining(arr));
	else
		return (free(buff), NULL);
}

char	*get_next_line(int fd)
{
	static char	*arr;

	return (ft_handleline(&arr, fd));
}