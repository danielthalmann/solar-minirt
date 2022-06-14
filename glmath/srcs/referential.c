/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   referential.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:30:44 by trossel           #+#    #+#             */
/*   Updated: 2022/06/14 07:20:44 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

t_ray	ray_to_referential(const t_referential *ref, const t_ray *world_ray)
{
	t_ray	ref_ray;

	v3f_copy(&ref_ray.origin, &world_ray->origin);
	v3f_minus_equal(&ref_ray.origin, &ref->p);
	ref_ray.origin = matrix_dot_v3f(ref->i, &ref_ray.origin);
	ref_ray.direction = matrix_dot_v3f(ref->i, &world_ray->direction);
	return (ref_ray);
}

t_ray	ray_from_referential(const t_referential *ref, const t_ray *ref_ray)
{
	t_ray	world_ray;

	v3f_copy(&world_ray.origin, &ref_ray->origin);
	world_ray.origin = matrix_dot_v3f(ref->b, &world_ray.origin);
	v3f_plus_equal(&world_ray.origin, &ref->p);
	world_ray.direction = matrix_dot_v3f(ref->b, &ref_ray->direction);
	return (world_ray);
}

void	referential_set_vec(t_referential *ref, t_v3f v, int idx)
{
	int	idx2;

	if (idx < 0 || idx > 2)
		return ;
	ref->b[idx] = v;
	v3f_normalize(&ref->b[idx]);
	idx2 = (idx + 1) % 3;
	ref->b[idx2] = v3f_cross_product(&(t_v3f){1.0f, 0.0f, 0.0f, 0.0f}, &ref->b[idx]);
	if (v3f_abs(&ref->b[idx2]) < 1e-6)
		ref->b[idx2] = v3f_cross_product(&(t_v3f){0.0f, 1.0f, 0.0f, 0.0f}, &ref->b[idx]);
	v3f_normalize(&ref->b[idx2]);
	ref->b[(idx2 + 1) % 3] = v3f_cross_product(&ref->b[idx2], &ref->b[idx]);
	v3f_normalize(&ref->b[(idx2 + 1) % 3]);
	inverse_matrix(ref->b, ref->i);
}
