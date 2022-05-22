/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:26:15 by trossel           #+#    #+#             */
/*   Updated: 2022/03/06 17:30:06 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "libft.h"

#define GNL_BUFFER_SIZE 32768

/**
 * s1 : output string
 * s2 : string to be appended to s1
 * n  : max number of bytes to append
 * */
static char	*ft_append(char *s1, char const *s2, size_t n)
{
	char	*s;
	char	*tmp;
	size_t	l;

	if (!s2 || n == 0)
		return (s1);
	l = ft_strlen(s2) + 1;
	if (s1)
		l += ft_strlen(s1);
	s = malloc(l * sizeof(char));
	if (!s)
		return (NULL);
	tmp = s;
	l = 0;
	while (s1 && s1[l])
		*(tmp++) = s1[l++];
	l = 0;
	while (*s2 && l < n)
		*(tmp++) = s2[l++];
	*tmp = '\0';
	if (s1)
		free(s1);
	return (s);
}

static void	gnl_split(char *src, char **leftover, char **line, const char *nl)
{
	char	*tmp;

	tmp = NULL;
	*line = ft_append(*line, src, nl - src + 1);
	if (*(nl + 1))
		tmp = ft_strdup(nl + 1);
	if (*leftover)
		free(*leftover);
	*leftover = tmp;
}

int	read_file_until_nl(int fd, char **leftover, char **nl)
{
	int		n_bytes;
	char	*buffer;

	buffer = malloc((GNL_BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (-1);
	*nl = NULL;
	if (*leftover)
		*nl = ft_strchr(*leftover, '\n');
	n_bytes = 1;
	while (!*nl && n_bytes != 0)
	{
		n_bytes = read(fd, buffer, GNL_BUFFER_SIZE);
		if (n_bytes < 0)
		{
			free(buffer);
			return (1);
		}
		buffer[n_bytes] = '\0';
		*nl = ft_strchr(buffer, '\n');
		*leftover = ft_append(*leftover, buffer, n_bytes);
	}
	free(buffer);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*leftover = {0};
	char		*nl;
	char		*line;

	nl = NULL;
	line = NULL;
	if (fd < 0)
		return (NULL);
	if (read_file_until_nl(fd, &leftover, &nl))
	{
		return (NULL);
	}
	if (leftover)
		nl = ft_strchr(leftover, '\n');
	if (!nl)
	{
		line = leftover;
		leftover = NULL;
	}
	else
		gnl_split(leftover, &leftover, &line, nl);
	return (line);
}
