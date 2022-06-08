/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:02:11 by trossel           #+#    #+#             */
/*   Updated: 2022/06/08 11:55:39 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"
#include "parse.h"
#include "ft_scanf.h"

#define N_ELEMENTS 4

#define ELEM "A"
#define INTENS_ERR "intensity"
#define UNIQUE_ERR "Error: can only have one object '%s' in a scene.\n"

static int	check_error(t_scene *s, int color[3], int n_parsed)
{
	int		err;
	float	range[2];

	range[0] = 0.0f;
	range[1] = 1.0f;
	err = parse_check_n_elem(N_ELEMENTS - n_parsed, ELEM);
	err += parse_check_in_range(s->ambient_intensity, range, INTENS_ERR, ELEM);
	err += parse_check_valid_color(color, ELEM);
	return (err);
}

int	parse_ambient_light(t_scene *scene, char *str)
{
	static char		has_parsed_already = 0;
	int				n_parsed;
	int				color[3];
	int				color_int;
	int				ret;

	if (has_parsed_already)
	{
		ft_fprintf(2, UNIQUE_ERR, ELEM);
		return (1);
	}
	n_parsed = ft_sscanf(str, ELEM" %f %d, %d, %d", &scene->ambient_intensity,
			&color[0], &color[1], &color[2]);
	color_int = (color[0] << 16) + (color[1] << 8) + color[2];
	scene->ambient = color_create_int(color_int);
	ret = check_error(scene, color, n_parsed);
	if (!ret)
		has_parsed_already = 1;
	return (ret);
}
