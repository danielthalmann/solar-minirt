/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 23:17:13 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/18 11:51:00 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int				mlx_int_find_in_pcm()
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
	t_color	c;
	t_sphere s;
	t_ray	r;

	s.origin.x = 0.0;
	s.origin.y = 0.0;
	s.origin.z = 20.0;
	s.rayon = 1.500;

	r.origin.x = 0.0;
	r.origin.y = 0.0;
	r.origin.z = -1.0;

	r.direction.x = -1.0 + (2 * ((float)x / (float)scene->w));
	r.direction.y = -1.0 + (2 * ((float)y / (float)scene->w));
	r.direction.z = 1.0;

	v3f_normalize(&r.direction);

	c.r = 0.2f;
	c.g = 0.2f;
	c.b = 0.2f;
	if (sphere_intersect(&r, &s))
	{
		c.r = 0.8;
		c.g = 0.8;
		c.b = 0.8;
	}
	app->pix_ptr[(int)(x + (y * scene->w))] = color_int(&c);
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

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	t_app	app;
	app.on_change = 1;
	app.mandel.range_min.x = -2.1;
	app.mandel.range_min.y = -1.1;
	app.mandel.zoom = 200;
	app.mandel.max_iter = 500;

	float ratio = 16.0 / 9.0;
	mlx_int_find_in_pcm();
	app.scene.h = 480;
	app.scene.w = app.scene.h * ratio;

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
