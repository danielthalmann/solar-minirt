/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:21:33 by trossel           #+#    #+#             */
/*   Updated: 2022/05/20 17:41:59 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

#define TITLE "=========\n| SCENE |\n=========\n"

static void	print_light(t_light *l)
{
	printf("\tLIGHT\n");
	printf("\torigin    = (%f, %f, %f)\n", l->origin.x,
		l->origin.y, l->origin.z);
	printf("\tintensity = %f\n", l->intensity);
	printf("\tcolor     = (%f, %f, %f)\n\n", l->color.r, l->color.g, l->color.b);
}

static void	print_shape(t_shape *s)
{
	if (s->type == SPHERE)
		sphere_print(&s->sphere);
	else if (s->type == CYLINDER)
	{
		printf("\tCYLINDER\n\torigin  = (%f, %f, %f)\n", s->cyl.origin.x,
			s->cyl.origin.y, s->cyl.origin.z);
		printf("\tnormale = (%f, %f, %f)\n", s->cyl.normal.x,
			s->cyl.normal.y, s->cyl.normal.z);
		printf("\tradius =  %f\n", s->cyl.radius);
		printf("\theight =  %f\n", s->cyl.height);
	}
	else if (s->type == PLANE)
	{
		printf("\tPLANE\n\torigin  = (%f, %f, %f)\n", s->plane.origin.x,
			s->plane.origin.y, s->plane.origin.z);
		printf("\tnormale = (%f, %f, %f)\n", s->plane.normal.x,
			s->plane.normal.y, s->plane.normal.z);
	}
	printf("\tcolor   = (%f, %f, %f)\n\n", s->color.r, s->color.g, s->color.b);
}

/* TODO: Remove printf */
void	print_scene(t_scene *s)
{
	t_shape	*shape;
	t_light	*light;

	printf(TITLE"(width, height)\t= (%d, %d)\n", s->w, s->h);
	printf("ambient color\t= (%f, %f, %f)\nAmb. intensity\t= %f\n",
		s->ambient.r, s->ambient.g, s->ambient.b, s->ambient_intensity);
	printf("Camera position\t= ");
	v3f_print(&s->cam.pos);
	printf("\nCamera orien\t= ");
	v3f_print(&s->cam.orien);
	printf("\nCamera FOV\t= %f rad (%f deg)\nShapes:\n\n", s->cam.fov,
		s->cam.fov * 180.0f / M_PI);
	shape = s->shapes;
	while (shape)
	{
		print_shape(shape);
		shape = shape->next;
	}
	printf("Lights:\n\n");
	light = s->lights;
	while (light)
	{
		print_light(light);
		light = light->next;
	}
}
