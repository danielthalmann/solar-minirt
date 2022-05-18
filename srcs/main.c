/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 23:17:13 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/18 16:28:19 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "glmath.h"

int	mlx_int_find_in_pcm()
{
	return (0);
}

int	on_close(void)
{
	exit(0);
}

void around(t_scene *scene, int x, int y, void *data)
{
//	unsigned int *ptr;
	t_app	*app;
	app = (t_app *)data;
	t_color	*c;
	t_ray	r;
	t_v3f	tmp_inter;
	t_shape	*shape;

	shape = scene->shapes;
	r.origin.x = 0.0;
	r.origin.y = 0.0;
	r.origin.z = -1.0;

	r.direction.x = -1.0 + (2 * ((float)x / (float)scene->w));
	r.direction.y = -1.0 + (2 * ((float)y / (float)scene->w));
	r.direction.z = 1.0;
	v3f_normalize(&r.direction);

	c = color_create(&scene->ambiant);
	while (shape)
	{
		if (shape->intersect(&r, &shape->shape, &tmp_inter))
		{
			c->r = 0.8;
			c->g = 0.8;
			c->b = 0.8;
		}
		shape = shape->next;
	}
	app->pix_ptr[(int)(x + (y * scene->w))] = color_int(c);
	free(c);
}

int	loop(void *param)
{
	t_app	*app;
	app = (t_app *)param;
	(void)param;

	if (app)
	{
		if (app->on_change)
		{
			int bpp, sl, endian;
			app->img_ptr = mlx_new_image(app->mlx_ptr, app->scene.w, app->scene.h);
			app->pix_ptr = (unsigned int *)mlx_get_data_addr(app->img_ptr, &(bpp), &(sl), &(endian));
			scene_around(&(app->scene), app, &around);
			mlx_put_image_to_window(app->mlx_ptr, app->win_ptr, app->img_ptr, 0, 0);
			app->on_change = 0;

		}
	}

	return (0);
}

static int	init_scene(t_scene *scene)
{
	t_shape	*shape;
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (1);
	shape = malloc(sizeof(t_shape));
	if (!shape)
		return (1);
	shape->type = SPHERE;
	shape->sphere.origin.x = 0.0;
	shape->sphere.origin.y = 0.0;
	shape->sphere.origin.z = 20.0;
	shape->sphere.radius = 1.500;
	shape->intersect = sphere_intersect;
	shape->next = NULL;
	scene->shapes = shape;
	light->origin.x = 50.0;
	light->origin.y = 50.0;
	light->origin.z = 0.0;
	light->intensity = 0.5;
	light->color.r = 0.6;
	light->color.g = 0.1;
	light->color.b = 0.1;
	light->next = NULL;
	scene->lights = light;
	scene->ambiant.r = 0.0;
	scene->ambiant.g = 0.0;
	scene->ambiant.b = 0.0;
	return (0);
}
int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	t_app	app;
	app.on_change = 1;

	float ratio = 16.0 / 9.0;
	mlx_int_find_in_pcm();
	app.scene.h = 480;
	app.scene.w = app.scene.h * ratio;
	init_scene(&app.scene);
	app.mlx_ptr = mlx_init();
	if (!app.mlx_ptr)
		return (0);
	app.win_ptr = mlx_new_window(app.mlx_ptr, app.scene.w, app.scene.h, "minirt");
	mlx_hook(app.win_ptr, MLX_EVT_DESTROY, 0L, &on_close, &app);
//	mlx_hook(app.win_ptr, MLX_EVT_KEYDN, 1L, &key_down, &app);
	mlx_hook(app.win_ptr, MLX_EVT_KEYUP, 2L, &key_up, &app);
	mlx_loop_hook(app.mlx_ptr, &loop, &app);


	mlx_loop(app.mlx_ptr);

	return (0);
}
