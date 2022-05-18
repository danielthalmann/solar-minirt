/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 10:26:45 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/18 11:47:58 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

int	sphere_intersect(t_ray *ray, t_sphere *sphere)
{
	t_v3f	oc;
	float	a;
	float	b;
	float	c;
	float	disc;

	oc = ray->origin;
	v3f_sub(&oc, &sphere->origin);
	a = v3f_dot(&ray->direction, &ray->direction);
	b = 2.0 * (v3f_dot(&oc, &ray->direction));
	c = v3f_dot(&oc, &oc) - sphere->rayon * sphere->rayon;
	disc = b*b - 4*a*c;
	if (disc < 0.0f)
    	return (0);
	return (1);
}

void	computeColorNormal(t_ray *ray, float dist, t_color *c, t_v3f *normal)
{
	(void)ray;
	(void)dist;
	(void)c;
	(void)normal;
	return ;
}
