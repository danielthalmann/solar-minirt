/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:02:11 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 12:23:21 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"
#include "parse.h"
#include "ft_scanf.h"
#include <unistd.h>

#define N_ELEMENTS 10

#define ELEM "sp"
#define RAD_ERR "diameter"

static int	check_error(t_scene *s, int color[3], int n_parsed)
{
	int	err;

	err = parse_check_n_elem(N_ELEMENTS - n_parsed, ELEM);
	err += parse_check_positive_float(s->shapes->sphere.radius, RAD_ERR, ELEM);
	err += parse_check_valid_color(color, ELEM);
	return (err);
}

static void	init_sphere(t_shape *s, int color[3])
{
	int	color_int;

	s->type = SPHERE;
	s->intersect = (int (*)(const t_ray *, const void *, t_point3f *))
		sphere_intersect;
	s->normal_ray = (void (*)(t_ray *, const void *))sphere_normal_ray;
	s->color_mask = (float (*)(const t_ray *, const void *))sphere_color_mask;
	s->color_normal = (t_color (*)(const t_ray *, const void *, float i))
		sphere_color_normal;
	s->color_texture = (t_color (*)(const t_ray *, const void *, t_image * i))
		sphere_color_texture;
	color_int = (color[0] << 16) + (color[1] << 8) + color[2];
	s->color = color_create_int(color_int);
	s->sphere.radius /= 2.0f;
}

int	parse_sphere(t_scene *scene, char *str)
{
	int		n_parsed;
	int		color[3];
	t_shape	*s;
	int		err;

	s = malloc(sizeof(t_shape));
	if (!s)
		return (1);
	init_shape(s);
	s->next = scene->shapes;
	scene->shapes = s;
	n_parsed = ft_sscanf(str, ELEM" %f, %f, %f %f %d, %d, %d %d %d %d",
			&s->sphere.origin.x, &s->sphere.origin.y, &s->sphere.origin.z,
			&s->sphere.radius, &color[0], &color[1], &color[2],
			&s->tex_id[0], &s->tex_id[1], &s->nm_id);
	err = check_error(scene, color, n_parsed);
	if (!err)
		init_sphere(s, color);
	return (err);
}
