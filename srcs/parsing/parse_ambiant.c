/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambiant.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:02:11 by trossel           #+#    #+#             */
/*   Updated: 2022/05/19 17:31:25 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "ft_scanf.h"

static int	check_error(t_scene *s, unsigned int color[3], int n_parsed)
{
	if (n_parsed != 4)
	{
		perror("Error: Incomplete camera description\n");
		return (1);
	}
	if (s->ambiant_intensity < 0 || s->ambiant_intensity > 1.0f)
	{
		perror("Error: ambiant intensity must be between 0 and 1 included.\n");
		return (1);
	}
	if (color[0] > 255 || color[1] > 255 || color[2] > 255)
	{
		perror("Error: color component must be between 0 and 255 included.\n");
		return (1);
	}
	return (0);
}

int	parse_ambiant_light(t_scene *scene, char *str)
{
	static char		has_parsed_already = 0;
	int				n_parsed;
	unsigned int	color[3];
	int				color_int;

	if (has_parsed_already)
		return (1);
	has_parsed_already = 1;
	n_parsed = ft_sscanf(str, "A %f %d,%d,%d", &scene->ambiant_intensity,
		&color[0], &color[1], &color[2]);
	color_int = (color[0] << 16) + (color[1] << 8) + color[2];
	scene->ambiant = color_create_int(color_int);
	return (check_error(scene, color, n_parsed));
}
