/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:02:11 by trossel           #+#    #+#             */
/*   Updated: 2022/06/03 16:17:36 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "ft_scanf.h"
#include <unistd.h>

#define N_ELEMENTS 7

#define ELEM "L"
#define INT_ERR "intensity"
#define UNIQUE_ERR "Error: can only have one object '%s' in a scene.\n"

static int	check_error(t_scene *s, int color[3], int n_parsed)
{
	int		err;
	float	range[2];

	range[0] = 0.0f;
	range[1] = 1.0f;
	err = parse_check_n_elem(N_ELEMENTS - n_parsed, ELEM);
	err += parse_check_in_range(s->lights->intensity, range, INT_ERR, ELEM);
	err += parse_check_valid_color(color, ELEM);
	return (err);
}

/*
 * For the mandatory part, only one light is allowed.
 */
int	parse_light(t_scene *scene, char *str)
{
	int				n_parsed;
	int				color[3];
	int				color_int;
	t_light			*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (1);
	light->next = scene->lights;
	scene->lights = light;
	n_parsed = ft_sscanf(str, ELEM" %f, %f, %f %f %d, %d, %d", &light->origin.x,
			&light->origin.y, &light->origin.z, &light->intensity,
			&color[0], &color[1], &color[2]);
	color_int = (color[0] << 16) + (color[1] << 8) + color[2];
	light->color = color_create_int(color_int);
	return (check_error(scene, color, n_parsed));
}
