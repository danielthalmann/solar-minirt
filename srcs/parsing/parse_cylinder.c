/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:02:11 by trossel           #+#    #+#             */
/*   Updated: 2022/06/15 08:54:39 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"
#include "parse.h"
#include "ft_scanf.h"
#include "libft.h"
#include <unistd.h>

#define N_ELEMENTS 12

#define ELEM "cy"
#define ORI_ERR "orientation"
#define RADIUS_ERR "diameter"
#define HEIGHT_ERR "height"

static int	check_error(t_scene *s, int color[3], int n_parsed)
{
	int	err;

	err = parse_check_n_elem(N_ELEMENTS - n_parsed, ELEM);
	err += parse_check_non_null_vector(&s->shapes->cyl.ref.b[1], ORI_ERR, ELEM);
	err += parse_check_positive_float(s->shapes->cyl.radius, RADIUS_ERR, ELEM);
	err += parse_check_positive_float(s->shapes->cyl.height, HEIGHT_ERR, ELEM);
	err += parse_check_valid_color(color, ELEM);
	return (err);
}

static void	init_cylinder(t_shape *s, int color[3], char *draw_checker)
{
	int	color_int;

	color_int = (color[0] << 16) + (color[1] << 8) + color[2];
	s->color = color_create_int(color_int);
	s->cyl.radius /= 2.0f;
	s->type = CYLINDER;
	s->intersect = (int (*)(const t_ray *, const void *, t_point3f *))
		cylinder_intersect;
	s->normal_ray = (void (*)(t_ray *, const void *))cylinder_normal_ray;
	s->color_mask = (float (*)(const t_ray *, const void *))
		cylinder_color_mask;
	s->color_normal = (t_color (*)(const t_ray *, const void *, float i))
		cylinder_color_normal;
	s->color_texture = (t_color (*)(const t_ray *, const void *, t_image * i))
		cylinder_color_texture;
	referential_set_vec(&s->cyl.ref, s->cyl.ref.b[1], 1);
	if (draw_checker && !ft_strcmp(draw_checker, "yes"))
		s->draw_checker = 1;
}

int	parse_cylinder(t_scene *scene, char *str)
{
	int				n_parsed;
	int				color[3];
	t_shape			*s;
	int				err;
	char			*draw_checker;

	s = malloc(sizeof(t_shape));
	if (!s)
		return (1);
	init_shape(s);
	s->next = scene->shapes;
	scene->shapes = s;
	draw_checker = NULL;
	n_parsed = ft_sscanf(str, ELEM" %f, %f, %f %f, %f, %f %f %f %d, %d, %d %ms",
			&s->cyl.ref.p.x, &s->cyl.ref.p.y, &s->cyl.ref.p.z,
			&s->cyl.ref.b[1].x, &s->cyl.ref.b[1].y, &s->cyl.ref.b[1].z,
			&s->cyl.radius, &s->cyl.height,
			&color[0], &color[1], &color[2], &draw_checker);
	err = check_error(scene, color, n_parsed);
	if (!err)
		init_cylinder(s, color, draw_checker);
	if (draw_checker)
		free(draw_checker);
	return (err);
}
