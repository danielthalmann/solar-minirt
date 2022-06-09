/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:02:11 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 12:28:40 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"
#include "parse.h"
#include "ft_scanf.h"
#include <unistd.h>

#define N_ELEMENTS 9

#define ELEM "pl"
#define ORI_ERR "orientation"

static int	check_error(t_scene *s, int color[3], int n_parsed)
{
	int	err;

	err = parse_check_n_elem(N_ELEMENTS - n_parsed, ELEM);
	err += parse_check_non_null_vector(&s->shapes->plane.normal, ORI_ERR, ELEM);
	err += parse_check_valid_color(color, ELEM);
	return (err);
}

int	parse_plane(t_scene *scene, char *str)
{
	int				n_parsed;
	int				color[3];
	int				color_int;
	t_shape			*s;

	s = malloc(sizeof(t_shape));
	if (!s)
		return (1);
	init_shape(s);
	s->next = scene->shapes;
	scene->shapes = s;
	s->type = PLANE;
	s->intersect = (int (*)(const t_ray *, const void *, t_point3f *))
		plane_intersect;
	s->normal_ray = (void (*)(t_ray *, const void *))plane_normal_ray;
	s->color_mask = (float (*)(const t_ray *, const void *))plane_color_mask;
	s->color_normal = (t_color (*)(const t_ray *, const void *, float i))plane_color_normal;
	s->color_texture = (t_color (*)(const t_ray *, const void *, t_image * i))plane_color_texture;
	n_parsed = ft_sscanf(str, ELEM " %f, %f, %f %f, %f, %f %d, %d, %d",
			&s->plane.origin.x, &s->plane.origin.y, &s->plane.origin.z,
			&s->plane.normal.x, &s->plane.normal.y, &s->plane.normal.z,
			&color[0], &color[1], &color[2]);
	v3f_normalize(&s->plane.normal);
	color_int = (color[0] << 16) + (color[1] << 8) + color[2];
	s->color = color_create_int(color_int);
	return (check_error(scene, color, n_parsed));
}
