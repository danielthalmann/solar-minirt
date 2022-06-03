/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:02:11 by trossel           #+#    #+#             */
/*   Updated: 2022/05/29 19:15:28 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"
#include "parse.h"
#include "ft_scanf.h"
#include <unistd.h>

#define N_ELEMENTS 11

#define ELEM "cy"
#define ORIEN_ERR "orientation vector cannot be null\n"
#define RADIUS_ERR "diameter"
#define HEIGHT_ERR "height"

static int	check_error(t_scene *s, int color[3], int n_parsed)
{
	int	err;

	err = parse_check_n_elem(N_ELEMENTS - n_parsed, ELEM);
	err += parse_check_non_null_vector(&s->shapes->cyl.normal, ORIEN_ERR, ELEM);
	err += parse_check_positive_float(s->shapes->cyl.radius, RADIUS_ERR, ELEM);
	err += parse_check_positive_float(s->shapes->cyl.height, HEIGHT_ERR, ELEM);
	err += parse_check_valid_color(color, ELEM);
	return (err);
}

int	parse_cylinder(t_scene *scene, char *str)
{
	int				n_parsed;
	int				color[3];
	int				color_int;
	t_shape			*s;

	s = malloc(sizeof(t_shape));
	if (!s)
		return (1);
	s->next = scene->shapes;
	scene->shapes = s;
	s->type = CYLINDER;
	s->intersect = (int (*)(const t_ray *, const void *, t_point3f *))cylinder_intersect;
	s->normal_ray = (void (*)(t_ray *, const void *))cylinder_normal_ray;
	n_parsed = ft_sscanf(str, ELEM" %f, %f, %f %f, %f, %f %f %f %d, %d, %d",
			&s->cyl.origin.x, &s->cyl.origin.y, &s->cyl.origin.z,
			&s->cyl.normal.x, &s->cyl.normal.y, &s->cyl.normal.z,
			&s->cyl.radius, &s->cyl.height,
			&color[0], &color[1], &color[2]);
	s->cyl.radius /= 2.0f;
	color_int = (color[0] << 16) + (color[1] << 8) + color[2];
	s->color = color_create_int(color_int);
	return (check_error(scene, color, n_parsed));
}
