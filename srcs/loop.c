/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:33:59 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 23:06:32 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "antialiasing.h"
#include "libft.h"

#define RENDER_TEXT "\rRendering...\t\t%3d %%"

const t_shape	*get_closest_shape(
		const t_shape *s, const t_ray *input_ray, t_ray *normal)
{
	const t_shape	*closest;
	float			closest_dist;
	float			dist;
	t_v3f			inter;

	closest = NULL;
	while (s)
	{
		if (s->intersect(input_ray, &s->shape, &inter))
		{
			dist = v3f_dist(&input_ray->origin, &inter);
			if (!closest || dist < closest_dist)
			{
				closest = s;
				v3f_copy(&normal->origin, &inter);
				closest_dist = dist;
			}
		}
		s = s->next;
	}
	if (closest)
		closest->normal_ray(normal, &closest->shape);
	return (closest);
}

static t_color	color_object_from_lights(const t_shape *shape, t_ray *r,
	t_scene *scene, t_ray *normale, t_light *l)
{
	t_color	c;

	c = color_create_int(0);
	if (get_light_ray(&normale->origin, l, scene->shapes))
	{
		if (shape->type == SPHERE)
		{
			c = color_add(c, compute_normal_texture(normale, shape, &scene->textures[0]));
			c = color_add(c, color_mult_c(compute_normal_texture(normale, shape, &scene->textures[1]), 0.8));
			c = color_mult(c, (compute_normal_mapping(normale, shape, l, &scene->textures[2])));
			//c = color_mult(c, (compute_diffuse_color(normale, shape, l, color_create_int(0xFFFFFFFF))));
		}
		else
		{
			c = color_add(c, compute_diffuse_color(normale, shape, l, shape->color));
		}
		c = color_add(c, compute_specular_color(r, normale, shape, l));
	}
	return (c);
}

void	around(t_scene *scene, int x, int y, void *data)
{
	t_color			c;
	t_ray			r;
	const t_shape	*shape;
	t_ray			normal_ray;
	t_light			*l;

	r = camera_init_ray(scene, x, y);
	c = color_create_int(0);
	shape = get_closest_shape(scene->shapes, &r, &normal_ray);
	if (shape)
	{
		l = scene->lights;
		c = color_mult_c(scene->ambient, scene->ambient_intensity);
		c = color_mult(c, shape->color);
		while (l)
		{
			c = color_add(c,
					color_object_from_lights(shape, &r, scene, &normal_ray, l));
			l = l->next;
		}
		if (shape->type != SPHERE)
			c = color_mult(c, compute_chess_color(&normal_ray, shape));
	}
	show_progress(RENDER_TEXT, y, scene->h - 1);
	set_image_color(&((t_app *)data)->img, x, y, c);
}

int	loop(void *param)
{
	t_app			*app;
	static float	angle = 0;

	app = (t_app *)param;
	if (!app)
		return (1);
	if (app->rotate_camera)
		angle += 0.1f;
	v3f_set(&app->scene.cam.pos, 10.0f * cosf(angle), 10.0f, 10.0f * sinf(angle));
	camera_update_orien(&app->scene.cam, v3f_dot_scalar(&app->scene.cam.pos, -1));
	v3f_normalize(&app->scene.cam.orien);
	app->on_change = 1;
	if (!app->on_change)
		return (0);
	scene_around(&(app->scene), app, &around);
	printf("\n");
	mlx_put_image_to_window(app->mlx, app->win_ptr, app->img.img_ptr, 0, 0);
	image_filter(&app->img, GAUSSIAN, 2);
	mlx_clear_window(app->mlx, app->win_ptr);
	mlx_put_image_to_window(app->mlx, app->win_ptr, app->img.img_ptr, 0, 0);
	app->on_change = 0;
	return (0);
}
