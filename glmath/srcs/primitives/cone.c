/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:12:35 by trossel           #+#    #+#             */
/*   Updated: 2022/06/10 15:38:22 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

#include <math.h>
#include <stdio.h>

void	cone_normal_ray(t_ray *normal, t_cone *cone)
{
	t_ray	r;
	t_v3f	tmp;

	r = ray_to_referential(&cone->ref, normal);
	if (r.origin.y >= cone->height)
		normal->direction = cone->ref.b[1];
	else if (r.origin.y <= 0)
		normal->direction = v3f_dot_scalar(&cone->ref.b[1], -1.0f);
	else
	{
		tmp = v3f_cross_product(&(t_v3f){0.0f, 1.0f, 0.0f, 0.0f}, &r.origin);
		r.direction = v3f_cross_product(&tmp, &r.origin);
		v3f_normalize(&r.direction);
		*normal = ray_from_referential(&cone->ref, &r);
	}
}

void	cone_print(const t_cone *cone)
{
	printf("\tCONE\n\torigin  = (%f, %f, %f)\n",
		cone->ref.p.x, cone->ref.p.y, cone->ref.p.z);
	printf("\tbase =      (%f, %f, %f)\n",
		cone->ref.b[0].x, cone->ref.b[1].x, cone->ref.b[2].x);
	printf("\t            (%f, %f, %f)\n",
		cone->ref.b[0].y, cone->ref.b[1].y, cone->ref.b[2].y);
	printf("\t            (%f, %f, %f)\n",
		cone->ref.b[0].z, cone->ref.b[1].z, cone->ref.b[2].z);
	printf("\tinv. base = (%f, %f, %f)\n",
		cone->ref.i[0].x, cone->ref.i[1].x, cone->ref.i[2].x);
	printf("\t            (%f, %f, %f)\n",
		cone->ref.i[0].y, cone->ref.i[1].y, cone->ref.i[2].y);
	printf("\t            (%f, %f, %f)\n",
		cone->ref.i[0].z, cone->ref.i[1].z, cone->ref.i[2].z);
	printf("\tradius =  %f\n", cone->radius);
	printf("\theight =  %f\n", cone->height);
}
