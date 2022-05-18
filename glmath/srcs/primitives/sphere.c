/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 10:26:45 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/18 09:13:09 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

int	sphere_intersect(t_ray *ray, t_sphere *sphere)
{
	t_v3f	dist;
	float	d;
	float	r;

	v3f_copy(&dist, &(sphere->origin));
	v3f_sub(&dist, &ray->origin);
	v3f_multi(&dist, &ray->direction);
	d = dist.x * dist.x + dist.y * dist.y + dist.z * dist.z;
	r = sphere->rayon * sphere->rayon * sphere->rayon; 
	if (r - d < 0.0f) 
    	return (1); 
	return (0);
}
 
void	computeColorNormal(t_ray *ray, float dist, t_color *c, t_v3f *normal)
{
	(void)ray;
	(void)dist;
	(void)c;
	(void)normal;
	return ;
}
