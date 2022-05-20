/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 08:52:49 by trossel           #+#    #+#             */
/*   Updated: 2022/05/20 11:40:51 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

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

static int	parse_line (t_scene *scene, char *line)
{
	char	*word;
	int		err;

	err = 0;
	if (line[0] == '\0' || line[0] == '#')
		return (0);
	word = get_first_word(line);
	if (!word)
		return (0);
	if (!ft_strcmp(word, "A"))
		err = parse_ambiant_light(scene, line);
	else if (!ft_strcmp(word, "C"))
		err = parse_camera(scene, line);
	// else if (!ft_strcmp(word, "L"))
	// 	err = parse_light(scene, line);
	// else if (!ft_strcmp(word, "pl"))
	// 	err = parse_plane(scene, line);
	// else if (!ft_strcmp(word, "sp"))
	// 	err = parse_sphere(scene, line);
	// else if (!ft_strcmp(word, "cy"))
	// 	err = parse_cylinder(scene, line);
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
		err = parse_line(scene, line);
		free(line);
		if (err)
			break;
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
	int	res;
	(void)scene;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("MiniRT: cannot open scene file");
		return (1);
	}
	res = parse_fd(scene, fd);
	close(fd);
	return (res);
}
