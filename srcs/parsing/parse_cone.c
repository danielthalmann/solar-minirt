/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:50:11 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 14:09:21 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"
#include "parse.h"
#include "ft_scanf.h"
#include <unistd.h>

#define N_ELEMENTS 11

#define ELEM "co"
#define ORI_ERR "orientation"
#define RADIUS_ERR "diameter"
#define HEIGHT_ERR "height"

static int	check_error(t_scene *s, int color[3], int n_parsed)
{
	int	err;

	err = parse_check_n_elem(N_ELEMENTS - n_parsed, ELEM);
	err += parse_check_non_null_vector(&s->shapes->cone.base[1], ORI_ERR, ELEM);
	err += parse_check_positive_float(s->shapes->cone.radius, RADIUS_ERR, ELEM);
	err += parse_check_positive_float(s->shapes->cone.height, HEIGHT_ERR, ELEM);
	err += parse_check_valid_color(color, ELEM);
	return (err);
}

static void	init_cone(t_shape *s, int color[3])
{
	int	color_int;

	color_int = (color[0] << 16) + (color[1] << 8) + color[2];
	s->color = color_create_int(color_int);
	s->cone.radius /= 2.0f;
	v3f_normalize(&s->cone.base[1]);
	if (fabsf(s->cone.base[1].z) < 1e-6 && fabsf(s->cone.base[1].x) < 1e-6)
		v3f_copy(&s->cone.base[2], &(t_v3f){0.0f, 0, 1.0f, 0});
	else
		s->cone.base[2] = v3f_cross_product(&(t_v3f){1.0f, 0.0f, 0.0f, 0.0f},
				&s->cone.base[1]);
	s->cone.base[0] = v3f_cross_product(&s->cone.base[1], &s->cone.base[2]);
	v3f_normalize(&s->cone.base[0]);
	v3f_normalize(&s->cone.base[2]);
	inverse_matrix(s->cone.base, s->cone.base_inv);
}

int	parse_cone(t_scene *scene, char *str)
{
	int				n_parsed;
	int				color[3];
	t_shape			*s;
	int				err;

	s = malloc(sizeof(t_shape));
	if (!s)
		return (1);
	s->next = scene->shapes;
	scene->shapes = s;
	s->type = CONE;
	s->intersect = (int (*)(const t_ray *, const void *, t_point3f *))
		cone_intersect;
	s->normal_ray = (void (*)(t_ray *, const void *))cone_normal_ray;
	s->color_mask = (float (*)(const t_ray *, const void *))cone_color_mask;
	s->color_normal = (t_color (*)(const t_ray *, const void *, float i))cone_color_normal;
	s->color_texture = (t_color (*)(const t_ray *, const void *, t_image * i))cone_color_texture;
	n_parsed = ft_sscanf(str, ELEM" %f, %f, %f %f, %f, %f %f %f %d, %d, %d",
			&s->cone.origin.x, &s->cone.origin.y, &s->cone.origin.z,
			&s->cone.base[1].x, &s->cone.base[1].y, &s->cone.base[1].z,
			&s->cone.radius, &s->cone.height,
			&color[0], &color[1], &color[2]);
	err = check_error(scene, color, n_parsed);
	if (!err)
		init_cone(s, color);
	return (err);
}
