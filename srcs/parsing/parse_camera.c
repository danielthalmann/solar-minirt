/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:51:07 by trossel           #+#    #+#             */
/*   Updated: 2022/05/20 11:17:14 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"
#include "parse.h"
#include "ft_scanf.h"

static int	check_error(t_scene *s, int n_parsed)
{
	if (n_parsed != 7)
	{
		perror("Error: Incomplete camera description\n");
		return (1);
	}
	if (v3f_abs(&s->cam.orien) == 0)
	{
		perror("Error: camera orientation vector cannot be null\n");
		return (1);
	}
	if (s->cam.fov < 0 || s->cam.fov > 180)
	{
		perror("Error: camera FOV must be between 0 and 180 included.\n");
		return (1);
	}
	return (0);
}

int	parse_camera(t_scene *s, char *str)
{
	static char		has_parsed_already = 0;
	int				n_parsed;

	if (has_parsed_already)
	{
		perror("Error: can only have one C (Camera) line in scene file.");
		return (1);
	}
	has_parsed_already = 1;
	n_parsed = ft_sscanf(str, "C %f, %f, %f %f, %f, %f %f", &s->cam.pos.x,
		&s->cam.pos.y, &s->cam.pos.z, &s->cam.orien.x, &s->cam.orien.y,
		&s->cam.orien.z, &s->cam.fov);
	v3f_normalize(&s->cam.orien);
	return (check_error(s, n_parsed));
}
