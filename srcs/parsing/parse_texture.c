/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 22:08:45 by dthalman          #+#    #+#             */
/*   Updated: 2022/06/10 23:28:08 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"
#include "parse.h"
#include "ft_scanf.h"
#include <unistd.h>

#define N_ELEMENTS 4
#define UV_ERR "UV"

#define ELEM "tex"

static int	check_error(t_texture *tex, int n_parsed)
{
	int	err;

	err = parse_check_n_elem(N_ELEMENTS - n_parsed, ELEM);
	err += parse_check_positive_float(tex->u, UV_ERR, ELEM);
	err += parse_check_positive_float(tex->v, UV_ERR, ELEM);
	return (err);
}

int	parse_texture(t_scene *scene, char *str)
{
	int			n_parsed;
	t_texture	*tex;
	int			err;

	tex = malloc(sizeof(t_texture));
	if (!tex)
		return (1);
	tex->next = scene->textures;
	scene->textures = tex;
	tex->loaded = 0;
	n_parsed = ft_sscanf(str, ELEM" %s %f,%f %f",
			&tex->filename, &tex->u, &tex->v, &tex->alpha);
	err = check_error(tex, n_parsed);
	return (err);
}
