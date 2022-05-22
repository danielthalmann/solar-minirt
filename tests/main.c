/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 23:17:13 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/20 22:32:22 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "glmath.h"


void plane_test()
{
	
	t_plane plane;
	plane.color.r = 1.0;
	plane.color.g = 0.5;
	plane.color.b = 0.5;
	plane.normal.x = 1.0;
	plane.normal.y = 0.0;
	plane.normal.z = 0.0;
	plane.origin.x = 0.0;
	plane.origin.y = 0.0;
	plane.origin.z = 5.0;

	v3f_print(&plane.origin);

	t_ray ray;
	ray.origin.x = 0.0;
	ray.origin.y = 0.0;
	ray.origin.z = -1.0;

	ray.direction.x = 0.0;
	ray.direction.y = 0.0;
	ray.direction.z = -1.0;
	v3f_normalize(&ray.direction);	

	plane_intersect(&ray, &plane, NULL);

	if (plane.origin.z > 0)
		return ;
		
}

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	plane_test();

	return (0);
}
