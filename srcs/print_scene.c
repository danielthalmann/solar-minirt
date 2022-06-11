/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:21:33 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 14:13:45 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

#define TITLE "=========\n| SCENE |\n=========\n"

static void	print_light(t_light *l)
{
	printf("Lights:\n\n");
	while (l)
	{
		printf("\tLIGHT\n");
		printf("\torigin    = (%f, %f, %f)\n", l->origin.x,
			l->origin.y, l->origin.z);
		printf("\tintensity = %f\n", l->intensity);
		printf("\tcolor     = (%f, %f, %f)\n\n", l->color.r, l->color.g,
			l->color.b);
		l = l->next;
	}
}

static void	print_shape(t_shape *s)
{
	if (s->type == SPHERE)
		sphere_print(&s->sphere);
	else if (s->type == CYLINDER)
		cylinder_print(&s->cyl);
	else if (s->type == PLANE)
		plane_print(&s->plane);
	else if (s->type == CONE)
		cone_print(&s->cone);
	printf("\tcolor   = (%f, %f, %f)\n", s->color.r, s->color.g, s->color.b);
	printf("\ttex id  = (%d, %d)\n", s->tex_id[0], s->tex_id[1]);
	printf("\tnm id   = (%d)\n\n", s->nm_id);
}

void	print_textures(t_texture *tex)
{
	int	idx;

	idx = 0;
	printf("Textures:\n\n");
	while (tex)
	{
		printf("\tTEXTURES\n");
		printf("\tindex     = (%d) \n", idx);
		printf("\tU V       = (%f, %f) \n", tex->u, tex->v);
		printf("\talpha     = (%f) \n", tex->alpha);
		printf("\tfilename  = (%s) \n\n", tex->filename);
		idx++;
		tex = tex->next;
	}
}

/* TODO: Remove printf */
void	print_scene(t_scene *s)
{
	t_shape	*shape;

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
	print_light(s->lights);
	print_textures(s->textures);
}
