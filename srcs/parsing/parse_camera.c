/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:51:07 by trossel           #+#    #+#             */
/*   Updated: 2022/05/20 17:38:37 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"
#include "parse.h"
#include "ft_scanf.h"

#define N_ELEMENTS 7

#define ELEM "C"
#define ORI_ERR "orientation"
#define FOV_ERR "fov"
#define UNIQUE_ERR "Error: can only have one object '%s' in a scene.\n"

static int	check_error(t_scene *s, int n_parsed)
{
	int		err;
	float	range[2];

	range[0] = 0.0f;
	range[1] = 180.0f;
	err = parse_check_n_elem(N_ELEMENTS - n_parsed, ELEM);
	err += parse_check_non_null_vector(&s->cam.orien, ORI_ERR, ELEM);
	err += parse_check_in_range(s->cam.fov, range, FOV_ERR, ELEM);
	return (err);
}

int	parse_camera(t_scene *s, char *str)
{
	static char	has_parsed_already = 0;
	int			n_parsed;
	int			err;

	if (has_parsed_already)
	{
		ft_fprintf(2, UNIQUE_ERR, ELEM);
		return (1);
	}
	has_parsed_already = 1;
	n_parsed = ft_sscanf(str, ELEM" %f, %f, %f %f, %f, %f %f", &s->cam.pos.x,
			&s->cam.pos.y, &s->cam.pos.z, &s->cam.orien.x, &s->cam.orien.y,
			&s->cam.orien.z, &s->cam.fov);
	v3f_normalize(&s->cam.orien);
	err = check_error(s, n_parsed);
	s->cam.fov *= M_PI / 180.0f;
	return (err);
}
