/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 09:21:29 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 12:31:38 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

void	init_shape(t_shape *s)
{
	if (!s)
		return ;
	s->next = NULL;
	s->intersect = NULL;
	s->color_mask = NULL;
	s->color_texture = NULL;
	s->type = SPHERE;
	s->color_normal = NULL;
	s->shininess = 50.0f;
	s->refl_coeff = 1.0f;
}

t_color	compute_chess_color(t_ray *normal_ray, const t_shape *shape)
{
	t_color	c;
	float	mask;

	c = color_create_int(0xFFFFFFFF);
	mask = shape->color_mask(normal_ray, &shape->shape);
	return (color_mult_c(c, mask));
}

t_color	compute_normal_color(
		t_ray *normal_ray, const t_shape *shape, float intensity)
{
	t_color	c;

	c.r = 0;
	c.g = 0;
	c.b = 0;
	if (shape->type == SPHERE)
		c = shape->color_normal(normal_ray, &shape->shape, intensity);
	return (c);
}

t_color	compute_normal_texture(
		t_ray *normal_ray, const t_shape *shape, t_image *textures)
{
	t_color	c;

	c.r = 0;
	c.g = 0;
	c.b = 0;
	if (shape->type == SPHERE)
		c = shape->color_texture(normal_ray, &shape->shape, textures);
	return (c);
}