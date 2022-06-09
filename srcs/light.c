/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:42:42 by trossel           #+#    #+#             */
/*   Updated: 2022/06/08 11:42:52 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"
#include "main.h"

char	get_light_ray(t_point3f *p, t_light *l, t_shape *shapes)
{
	const t_shape	*closest;
	t_ray	light_ray;
	t_ray	inter;

	light_ray.origin = *p;
	light_ray.direction = l->origin;
	v3f_minus_equal(&light_ray.direction, p);
	v3f_normalize(&light_ray.direction);
	closest = get_closest_shape(shapes, &light_ray, &inter);
	if (closest && v3f_dist(p, &l->origin) > v3f_dist(p, &inter.origin))
		return (0);
	return (1);
}
