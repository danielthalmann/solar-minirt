/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 10:26:45 by dthalman          #+#    #+#             */
/*   Updated: 2022/06/10 15:37:51 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

#include <stdio.h>

void	cylinder_normal_ray(t_ray *normal, t_cylinder *cyl)
{
	t_ray	r;

	r = ray_to_referential(&cyl->ref, normal);
	if (r.origin.y >= cyl->height)
		normal->direction = cyl->ref.b[1];
	else if (r.origin.y <= 0)
		normal->direction = v3f_dot_scalar(&cyl->ref.b[1], -1.0f);
	else
	{
		r.direction = r.origin;
		r.direction.y = 0;
		v3f_normalize(&r.direction);
		*normal = ray_from_referential(&cyl->ref, &r);
	}
}

void	cylinder_print(const t_cylinder *cyl)
{
	printf("\tCYLINDER\n\torigin  = (%f, %f, %f)\n",
		cyl->ref.p.x, cyl->ref.p.y, cyl->ref.p.z);
	printf("\tbase =      (%f, %f, %f)\n",
		cyl->ref.b[0].x, cyl->ref.b[1].x, cyl->ref.b[2].x);
	printf("\t            (%f, %f, %f)\n",
		cyl->ref.b[0].y, cyl->ref.b[1].y, cyl->ref.b[2].y);
	printf("\t            (%f, %f, %f)\n",
		cyl->ref.b[0].z, cyl->ref.b[1].z, cyl->ref.b[2].z);
	printf("\tinv. base = (%f, %f, %f)\n",
		cyl->ref.i[0].x, cyl->ref.i[1].x, cyl->ref.i[2].x);
	printf("\t            (%f, %f, %f)\n",
		cyl->ref.i[0].y, cyl->ref.i[1].y, cyl->ref.i[2].y);
	printf("\t            (%f, %f, %f)\n",
		cyl->ref.i[0].z, cyl->ref.i[1].z, cyl->ref.i[2].z);
	printf("\tradius =  %f\n", cyl->radius);
	printf("\theight =  %f\n", cyl->height);
}
