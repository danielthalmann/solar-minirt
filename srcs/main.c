/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 23:17:13 by dthalman          #+#    #+#             */
/*   Updated: 2022/06/08 12:29:20 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "export_ppm.h"
#include "error.h"
#include "glmath.h"
#include "libft.h"
#include "mlx.h"
#include "parsing/parse.h"
#include <unistd.h>

int	on_close(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	free_app(app);
	exit(0);
}

const t_shape	*get_closest_shape(const t_shape *s, const t_ray *input_ray, t_ray *normal)
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

t_color	compute_chess_color(t_ray *normal_ray, const t_shape *shape)
{
	t_color	c;
	float	mask;

	c = color_create_int(0xFFFFFFFF);
	mask = shape->color_mask(normal_ray, &shape->shape);
	return (color_mult_c(c, mask));
}

t_color	compute_normal_color(t_ray *normal_ray, const t_shape *shape, float intensity)
{
	t_color	c;

	c.r = 0;
	c.g = 0;
	c.b = 0;
	if (shape->type == SPHERE)
		c = shape->color_normal(normal_ray, &shape->shape, intensity);
	return (c);
}

t_color	compute_normal_texture(t_ray *normal_ray, const t_shape *shape, t_image *textures)
{
	t_color	c;

	c.r = 0;
	c.g = 0;
	c.b = 0;
	if (shape->type == SPHERE)
		c = shape->color_texture(normal_ray, &shape->shape, textures);
	return (c);
}

static t_color	color_object_from_lights(const t_shape *shape, t_ray *r,
	t_scene *scene, t_ray *normale, t_light *l)
{
	t_color	c;

	c = color_mult_c(scene->ambient, scene->ambient_intensity);
	if(get_light_ray(&normale->origin, l, scene->shapes))
	{
		c = color_mult_c(scene->ambient, scene->ambient_intensity);
		if (shape->type == SPHERE)
		{
			c = color_add(c, compute_normal_texture(normale, shape, &scene->textures[0]));
			c = color_add(c, color_mult_c(compute_normal_texture(normale, shape, &scene->textures[1]), 0.8));
			c = color_mult(c, (compute_diffuse_color(normale, shape, l, color_create_int(0xFFFFFFFF))));
			//c = color_mult(c2, compute_chess_color(&normal_ray, shape));
		}
		else
		{
			c = color_add(c, compute_diffuse_color(normale, shape, l, shape->color));
			c = color_mult(c, compute_chess_color(normale, shape));
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
		while (l)
		{
			c = color_add(c, color_object_from_lights(shape, &r, scene, &normal_ray, l));
			l = l->next;
		}
	}
	ft_printf("\rRendering... (%d %%)",
			100 * (y * scene->w + x) / (scene->w * scene->h));
	img_set_pixel(((t_app *)data)->img, x, y, color_int(&c));
}

int	loop(void *param)
{
	t_app	*app;
	static float angle = 0;

	app = (t_app *)param;
	if (!app)
		return (1);
	if (app->rotate_camera)
		angle += 0.1f;
	v3f_set(&app->scene.cam.pos, 10.0f * cosf(angle), 10.0f, 10.0f * sinf(angle));
	camera_update_orien(&app->scene.cam, v3f_dot_scalar(&app->scene.cam.pos, -1));
	v3f_normalize(&app->scene.cam.orien);
	app->on_change = 1;

	if (app->on_change)
	{
		win_clear(app->win);
		img_clear(app->img);
		scene_around(&(app->scene), app, &around);
		img_draw_to_win(app->img, app->win, 0, 0);
		app->on_change = 0;
	}

	return (0);
}

static int	init_mlx(t_app *app, int w, int h)
{
	app->gfx_ctx = gfx_init();
	app->win = win_init(app->gfx_ctx, w, h, "Solar MiniRT");
	app->img = img_init(app->gfx_ctx, w, h);
	if (!app->gfx_ctx || !app->win || !app->img)
		return (1);
	app->scene.textures = malloc(3 * sizeof(t_image));
	load_texture_xpm("textures/2k_earth_daymap.xpm", app->mlx_ptr, &app->scene.textures[0]);
	load_texture_xpm("textures/2k_earth_clouds.xpm", app->mlx_ptr, &app->scene.textures[1]);
	load_texture_xpm("textures/2k_earth_normal_map.xpm", app->mlx_ptr, &app->scene.textures[2]);
	mlx_hook(app->win->mlx_win, MLX_EVT_DESTROY, 0L, &on_close, app);
	mlx_hook(app->win->mlx_win, MLX_EVT_KEYUP, 2L, &key_up, app);
	gfx_loop_hook(app->gfx_ctx, &loop, app);
	return (0);
}

int	main(int argc, char **argv)
{
	t_app	app;

	app.on_change = 1;
	app.rotate_camera = 1;
	app.scene.ratio = 16.0 / 9.0;
	app.scene.h = 480;
	app.scene.w = app.scene.h * app.scene.ratio;
	app.scene.shapes = NULL;
	app.scene.lights = NULL;
	if (argc < 2)
		return (notEnoughArguments());
	if (parse(&app.scene, argv[1]))
		return (1);
	print_scene(&app.scene);
	if (init_mlx(&app, app.scene.w, app.scene.h))
		return (1);
	if (argc == 3 && !ft_strcmp(argv[2], "-e"))
	{
		loop(&app);
		export_ppm("export.ppm", &app);
	}
	else
		gfx_loop(app.gfx_ctx);
	return (0);
}
