/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffusion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:15:29 by trossel           #+#    #+#             */
/*   Updated: 2022/06/08 11:17:24 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

t_color	compute_diffuse_color(t_ray *normal_ray, const t_shape *shape,
		const t_light *light, const t_color color)
{
	t_v3f	il;
	float	dot;
	t_color	c;

	c = color_create_int(0);
	v3f_copy(&il, &light->origin);
	v3f_minus_equal(&il, &normal_ray->origin);
	v3f_normalize(&il);
	dot = v3f_scalar_product(&normal_ray->direction, &il);
	dot *= light->intensity;
	if (dot < 0.0f)
	{
		if (shape->type == PLANE)
			dot = -dot;
		else
			return (c);
	}
	c = color_mult_c(color, dot);
	return (c);
}
