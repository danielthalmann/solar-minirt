/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:50:11 by trossel           #+#    #+#             */
/*   Updated: 2022/06/14 07:28:47 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"
#include "parse.h"
#include "ft_scanf.h"
#include <unistd.h>

#define N_ELEMENTS 11

#define ELEM "co"
#define ORI_E "orientation"
#define RADIUS_ER "diameter"
#define HEIGHT_ER "height"

static int	check_error(t_scene *s, int color[3], int n_parsed)
{
	int	err;

	err = parse_check_n_elem(N_ELEMENTS - n_parsed, ELEM);
	err += parse_check_non_null_vector(&s->shapes->cone.ref.b[1], ORI_E, ELEM);
	err += parse_check_positive_float(s->shapes->cone.radius, RADIUS_ER, ELEM);
	err += parse_check_positive_float(s->shapes->cone.height, HEIGHT_ER, ELEM);
	err += parse_check_valid_color(color, ELEM);
	return (err);
}

static void	init_cone(t_shape *s, int color[3])
{
	int	color_int;

	s->type = CONE;
	s->intersect = (int (*)(const t_ray *, const void *, t_point3f *))
		cone_intersect;
	s->normal_ray = (void (*)(t_ray *, const void *))cone_normal_ray;
	s->color_mask = (float (*)(const t_ray *, const void *))cone_color_mask;
	s->color_normal = (t_color (*)(const t_ray *, const void *, float i))
		cone_color_normal;
	s->color_texture = (t_color (*)(const t_ray *, const void *, t_image * i))
		cone_color_texture;
	color_int = (color[0] << 16) + (color[1] << 8) + color[2];
	s->color = color_create_int(color_int);
	s->cone.radius /= 2.0f;
	v3f_normalize(&s->cone.ref.b[1]);
	if (fabsf(s->cone.ref.b[1].z) < 1e-6 && fabsf(s->cone.ref.b[1].x) < 1e-6)
		v3f_copy(&s->cone.ref.b[2], &(t_v3f){0.0f, 0, 1.0f, 0});
	else
		s->cone.ref.b[2] = v3f_cross_product(&(t_v3f){1.0f, 0.0f, 0.0f, 0.0f},
				&s->cone.ref.b[1]);
	s->cone.ref.b[0] = v3f_cross_product(&s->cone.ref.b[1], &s->cone.ref.b[2]);
	v3f_normalize(&s->cone.ref.b[0]);
	v3f_normalize(&s->cone.ref.b[2]);
	inverse_matrix(s->cone.ref.b, s->cone.ref.i);
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
	n_parsed = ft_sscanf(str, ELEM" %f, %f, %f %f, %f, %f %f %f %d, %d, %d",
			&s->cone.ref.p.x, &s->cone.ref.p.y, &s->cone.ref.p.z,
			&s->cone.ref.b[1].x, &s->cone.ref.b[1].y, &s->cone.ref.b[1].z,
			&s->cone.radius, &s->cone.height,
			&color[0], &color[1], &color[2]);
	err = check_error(scene, color, n_parsed);
	if (!err)
		init_cone(s, color);
	return (err);
}
