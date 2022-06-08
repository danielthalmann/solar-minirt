/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 10:26:45 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/30 14:53:13 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

#include <stdio.h>

/* Used the formula described here:
 * https://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html
 */
int	cylinder_intersect(const t_ray *ray, const t_cylinder *cyl,
		t_point3f *intersec)
{
	(void)intersec;
	(void)cyl;
	(void)ray;
	return (0);
}

void	cylinder_normal_ray(t_ray *normal, t_cylinder *cyl)
{
	(void)normal;
	(void)cyl;
}

float	cylinder_color_mask(const t_ray *normale, const t_cylinder *cyl)
{
	(void)normale;
	(void)cyl;
	return (1.0f);
}

t_color	cylinder_color_normal(const t_ray *normale, const t_cylinder *cyl, float intensity)
{
	t_color	c;

	(void) normale;
	(void) cyl;
	(void) intensity;
	c = color_create_int(0);	
	return (c);
}

void	cylinder_print(const t_cylinder *cyl)
{
	printf("\tCYLINDER\n\torigin  = (%f, %f, %f)\n", cyl->origin.x,
		cyl->origin.y, cyl->origin.z);
	printf("\tnormale = (%f, %f, %f)\n", cyl->normal.x,
		cyl->normal.y, cyl->normal.z);
	printf("\tradius =  %f\n", cyl->radius);
	printf("\theight =  %f\n", cyl->height);
}
