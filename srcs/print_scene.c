/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:21:33 by trossel           #+#    #+#             */
/*   Updated: 2022/05/20 11:10:09 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

static void	print_light(t_light *l)
{
	printf("\tLIGHT\n");
	printf("\torigin = (%f, %f, %f)\n", l->origin.x,
		l->origin.y, l->origin.z);
	printf("\tintensity = %f\n", l->intensity);
	printf("\tcolor = (%f, %f, %f)\n\n", l->color.r, l->color.g, l->color.b);
}

static void	print_shape(t_shape *s)
{
	if (s->type == SPHERE)
		sphere_print(&s->sphere);
	else if (s->type == CYLINDER)
	{
		printf("\tCYLINDER\n\torigin = (%f, %f, %f)\n", s->cyl.origin.x,
			s->cyl.origin.y, s->cyl.origin.z);
		printf("\tnormale = (%f, %f, %f)\n", s->cyl.normal.x,
			s->cyl.normal.y, s->cyl.normal.z);
		printf("\tradius = %f\n", s->cyl.radius);
		printf("\theight = %f\n", s->cyl.height);
	}
	else if (s->type == PLANE)
	{
		printf("\tPLANE\n\torigin = (%f, %f, %f)\n", s->plane.origin.x,
			s->plane.origin.y, s->plane.origin.z);
		printf("\tnormale = (%f, %f, %f)\n", s->plane.normal.x,
			s->plane.normal.y, s->plane.normal.z);
	}
	printf("\tcolor = (%f, %f, %f)\n\n", s->color.r, s->color.g, s->color.b);
}

void	print_scene(t_scene *s)
{
	t_shape	*shape;
	t_light	*light;

	printf("=======\nSCENE :\n=======\n");
	printf("(w, h) = (%d, %d)\n", s->w, s->h);
	printf("Ambiant color: (%f, %f, %f) intensity = %f\n", s->ambiant.r,
		s->ambiant.g, s->ambiant.b, s->ambiant_intensity);
	printf("Camera position: ");
	v3f_print(&s->cam.pos);
	printf("\nCamera orientation: ");
	v3f_print(&s->cam.orien);
	printf("\nCamera FOV: %f\nShapes:\n\n", s->cam.fov);
	shape = s->shapes;
	while (shape)
	{
		print_shape(shape);
		shape = shape->next;
	}
	printf("Lights:\n");
	light = s->lights;
	while (light)
	{
		print_light(light);
		light = light->next;
	}
}
