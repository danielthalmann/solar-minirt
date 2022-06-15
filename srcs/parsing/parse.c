/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 08:52:49 by trossel           #+#    #+#             */
/*   Updated: 2022/06/15 08:45:18 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"
#include "../main.h"

#include <fcntl.h>
#include <unistd.h>

#define UNKNOWN_LINE_ERR "Warning: %s: skipped unknown object\n"
#define FILE_OPEN_ERR "Error: %s: "
/*
 * set is the set of characters representing the end of the word.
 * By default, it is set to all whitespaces.
 * */
static char	*get_first_word(const char *str)
{
	int		length;

	length = 0;
	if (!str)
		return (NULL);
	while (str[length] != '\0' && !ft_is_white_space(str[length]))
		length++;
	return (ft_substr(str, 0, length));
}

static int	parse_first_word(const char *word, t_scene *scene, char *line)
{
	if (!ft_strcmp(word, "A"))
		return (parse_ambient_light(scene, line));
	else if (!ft_strcmp(word, "C"))
		return (parse_camera(scene, line));
	else if (!ft_strcmp(word, "L"))
		return (parse_light(scene, line));
	else if (!ft_strcmp(word, "pl"))
		return (parse_plane(scene, line));
	else if (!ft_strcmp(word, "sp"))
		return (parse_sphere(scene, line));
	else if (!ft_strcmp(word, "cy"))
		return (parse_cylinder(scene, line));
	else if (!ft_strcmp(word, "co"))
		return (parse_cone(scene, line));
	else if (!ft_strcmp(word, "tex"))
		return (parse_texture(scene, line));
	else
		ft_fprintf(STDERR_FILENO, UNKNOWN_LINE_ERR, word);
	return (0);
}

static int	parse_line(t_scene *scene, char *line)
{
	char	*word;
	int		err;

	err = 0;
	if (line[0] == '\0' || line[0] == '#')
		return (0);
	word = get_first_word(line);
	if (!word)
		return (0);
	err = parse_first_word(word, scene, line);
	free(word);
	return (err);
}

static int	parse_fd(t_scene *scene, int fd)
{
	char	*tmp;
	char	*line;
	int		err;

	err = 0;
	tmp = get_next_line(fd);
	line = ft_strtrim(tmp, NULL);
	if (tmp)
		free(tmp);
	while (line)
	{
		err += parse_line(scene, line);
		free(line);
		tmp = get_next_line(fd);
		line = ft_strtrim(tmp, NULL);
		if (tmp)
			free(tmp);
	}
	return (err);
}

int	parse(t_scene *scene, char *filename)
{
	int	fd;
	int	err;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_fprintf(STDERR_FILENO, FILE_OPEN_ERR, filename);
		perror(NULL);
		return (1);
	}
	err = parse_fd(scene, fd);
	close(fd);
	err += parse_check_scene(scene);
	if (err)
		free_scene(scene);
	return (err);
}
