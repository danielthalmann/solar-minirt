/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:02:11 by trossel           #+#    #+#             */
/*   Updated: 2022/06/07 19:24:49 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"
#include "parse.h"
#include "ft_scanf.h"
#include <unistd.h>

#define N_ELEMENTS 11

#define ELEM "cy"
#define ORI_ERR "orientation"
#define RADIUS_ERR "diameter"
#define HEIGHT_ERR "height"

static int	check_error(t_scene *s, int color[3], int n_parsed)
{
	int	err;

	err = parse_check_n_elem(N_ELEMENTS - n_parsed, ELEM);
	err += parse_check_non_null_vector(&s->shapes->cyl.base[1], ORI_ERR, ELEM);
	err += parse_check_positive_float(s->shapes->cyl.radius, RADIUS_ERR, ELEM);
	err += parse_check_positive_float(s->shapes->cyl.height, HEIGHT_ERR, ELEM);
	err += parse_check_valid_color(color, ELEM);
	return (err);
}

static void	init_cylinder(t_shape *s, int color[3])
{
	int	color_int;

	color_int = (color[0] << 16) + (color[1] << 8) + color[2];
	s->color = color_create_int(color_int);
	s->cyl.radius /= 2.0f;
	v3f_normalize(&s->cyl.base[1]);
	if (fabsf(s->cyl.base[1].z) < 1e-6 && fabsf(s->cyl.base[1].x) < 1e-6)
		v3f_copy(&s->cyl.base[2], &(t_v3f){0.0f, 0, 1.0f, 0});
	else
		s->cyl.base[2] = v3f_cross_product(&(t_v3f){1.0f, 0.0f, 0.0f, 0.0f},
				&s->cyl.base[1]);
	s->cyl.base[0] = v3f_cross_product(&s->cyl.base[1], &s->cyl.base[2]);
	v3f_normalize(&s->cyl.base[0]);
	v3f_normalize(&s->cyl.base[2]);
	inverse_matrix(s->cyl.base, s->cyl.base_inv);
}

int	parse_cylinder(t_scene *scene, char *str)
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
	s->type = CYLINDER;
	s->intersect = (int (*)(const t_ray *, const void *, t_point3f *))
		cylinder_intersect;
	s->normal_ray = (void (*)(t_ray *, const void *))cylinder_normal_ray;
	s->color_mask = (float (*)(const t_ray *, const void *))cylinder_color_mask;
	s->color_normal = (t_color (*)(const t_ray *, const void *, float i))cylinder_color_normal;
	s->color_texture = (t_color (*)(const t_ray *, const void *, t_image * i))cylinder_color_texture;
	n_parsed = ft_sscanf(str, ELEM" %f, %f, %f %f, %f, %f %f %f %d, %d, %d",
			&s->cyl.origin.x, &s->cyl.origin.y, &s->cyl.origin.z,
			&s->cyl.base[1].x, &s->cyl.base[1].y, &s->cyl.base[1].z,
			&s->cyl.radius, &s->cyl.height,
			&color[0], &color[1], &color[2]);
	err = check_error(scene, color, n_parsed);
	if (!err)
		init_cylinder(s, color);
	return (err);
}
