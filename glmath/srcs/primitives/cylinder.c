/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 10:26:45 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/25 14:29:23 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

#include <stdio.h>

/* Used the formula described here:
 * https://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html
 */
int	cylinder_intersect(t_ray *ray, t_cylinder *cyl, t_point3f *intersec)
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

void	cylinder_print(t_cylinder *cyl)
{
	printf("\tCYLINDER\n\torigin  = (%f, %f, %f)\n", cyl->origin.x,
		cyl->origin.y, cyl->origin.z);
	printf("\tnormale = (%f, %f, %f)\n", cyl->normal.x,
		cyl->normal.y, cyl->normal.z);
	printf("\tradius =  %f\n", cyl->radius);
	printf("\theight =  %f\n", cyl->height);
}
