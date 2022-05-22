/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 23:17:13 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/22 14:23:31 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	planeTest(void)
{
	t_plane	plane;
	t_ray	ray;

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
	ray.origin.x = 0.0;
	ray.origin.y = 0.0;
	ray.origin.z = -1.0;
	ray.direction.x = 0.0;
	ray.direction.y = 0.0;
	ray.direction.z = -1.0;
	v3f_normalize(&ray.direction);
	plane_intersect(&ray, &plane, NULL);
	if (plane.origin.z > 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	if (argc != 2)
		return (notEnoughArguments());
	else if (!ft_strcmp(argv[1], "-h"))
		return (help());
	else if (!ft_strcmp(argv[1], "-parser"))
		return (parserTest());
	else if (!ft_strcmp(argv[1], "-plane"))
		return (planeTest());
	return (0);
}
