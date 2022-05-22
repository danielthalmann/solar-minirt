/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 23:17:13 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/20 17:16:36 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "error.h"
#include "glmath.h"
#include "parsing/parse.h"
#include <unistd.h>

int	on_close(void)
{
	exit(0);
}

t_shape	*get_closest_shape(t_shape *shape, t_ray *ray)
{
	t_shape	*closest;
	float	closest_dist;
	float	dist;
	t_v3f	inter_pt;

	closest = NULL;
	while (shape)
	{
		if (shape->intersect(ray, &shape->shape, &inter_pt))
		{
			dist = v3f_dist(&ray->origin, &inter_pt);
			if (!closest || dist < closest_dist)
			{
				closest = shape;
				closest_dist = dist;
			}
		}
		shape = shape->next;
	}
	return (closest);
}

void around(t_scene *scene, int x, int y, void *data)
{
	t_app	*app;
	app = (t_app *)data;
	t_color	*c;
	t_ray	r;
	t_shape	*shape;

	r.origin.x = scene->cam.pos.x;
	r.origin.y = scene->cam.pos.y;
	r.origin.z = scene->cam.pos.z;

	r.direction.x = -1.0 + (2 * ((float)x / (float)scene->w));
	r.direction.y = -1.0 + (2 * ((float)y / (float)scene->w)) + ((float)(scene->w - scene->h) / (float)scene->w);
	r.direction.z = 1.0;
	v3f_normalize(&r.direction);

	shape = get_closest_shape(scene->shapes, &r);
	c = color_create(&scene->ambiant);
	c->r *= scene->ambiant_intensity;
	c->g *= scene->ambiant_intensity;
	c->b *= scene->ambiant_intensity;
	if (shape)
	{
		c->r = shape->color.r;
		c->g = shape->color.g;
		c->b = shape->color.b;
	}
	app->pix_ptr[(int)(x + (y * scene->w))] = color_int(c);
	free(c);
}

int	loop(void *param)
{
	t_app	*app;
	app = (t_app *)param;
	(void)param;

	if (!app)
		return (1);
	if (app->on_change)
	{
		int bpp, sl, endian;
		app->img_ptr = mlx_new_image(app->mlx_ptr, app->scene.w, app->scene.h);
		app->pix_ptr = (unsigned int *)mlx_get_data_addr(app->img_ptr, &(bpp), &(sl), &(endian));
		scene_around(&(app->scene), app, &around);
		mlx_put_image_to_window(app->mlx_ptr, app->win_ptr, app->img_ptr, 0, 0);
		app->on_change = 0;
	}

	return (0);
}

int	main(int argc, char **argv)
{
	t_app	app;
	app.on_change = 1;

	float ratio = 16.0 / 9.0;
	app.scene.h = 480;
	app.scene.w = app.scene.h * ratio;
	app.scene.shapes = NULL;
	app.scene.lights = NULL;
	if (argc < 2)
		return (notEnoughArguments());
	if (parse(&app.scene, argv[1]))
		return (1);
	print_scene(&app.scene);
	return (0);						// <-	PROTIP: REMOVE THIS LINE TO SEGFAULT
									//		due to missing *func for objects
									//		plane and cylinder
	app.mlx_ptr = mlx_init();
	if (!app.mlx_ptr)
		return (0);
	app.win_ptr = mlx_new_window(app.mlx_ptr, app.scene.w, app.scene.h, "minirt");
	mlx_hook(app.win_ptr, MLX_EVT_DESTROY, 0L, &on_close, &app);
	mlx_hook(app.win_ptr, MLX_EVT_KEYUP, 2L, &key_up, &app);
	mlx_loop_hook(app.mlx_ptr, &loop, &app);


	mlx_loop(app.mlx_ptr);

	return (0);
}
