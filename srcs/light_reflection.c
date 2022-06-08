/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_reflection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:20:09 by trossel           #+#    #+#             */
/*   Updated: 2022/06/08 11:25:03 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

static t_v3f	compute_reflection_vector(t_v3f input_vec, t_v3f normale)
{
	t_v3f	tmp;
	float	scalar;
	t_v3f	reflection_vec;

	v3f_copy(&reflection_vec, &input_vec);
	scalar = 2 * v3f_scalar_product(&input_vec, &normale);
	tmp = v3f_dot_scalar(&normale, scalar);
	v3f_minus_equal(&reflection_vec, &tmp);
	return (reflection_vec);
}

t_color	compute_specular_color(const t_ray *input_ray, const t_ray *normal_ray,
			const t_shape *shape, const t_light *light)
{
	t_color	c;
	float	dot;
	t_v3f	reflec;
	t_v3f	light_vec;
	float	alpha;
	float	k_s;

	alpha = 50.0f;
	k_s = 1.0f;
	(void)shape;
	c = color_create_int(0);
	light_vec = normal_ray->origin;
	v3f_minus_equal(&light_vec, &light->origin);
	v3f_normalize(&light_vec);
	reflec = compute_reflection_vector(light_vec, normal_ray->direction);
	dot = - v3f_scalar_product(&reflec, &input_ray->direction);
	if (dot < 0)
		return (c);
	dot = k_s * powf(dot, alpha);
	c = color_mult_c(light->color, dot * light->intensity);
	return (c);
}
