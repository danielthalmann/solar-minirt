/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 23:17:13 by dthalman          #+#    #+#             */
/*   Updated: 2022/06/08 11:17:11 by trossel          ###   ########.fr       */
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

static const t_shape	*get_closest_shape(const t_shape *s, const t_ray *input_ray, t_ray *normal)
{
	const t_shape	*closest;
	float	closest_dist;
	float	dist;
	t_v3f	inter;

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

static t_v3f	compute_reflection_vector(t_v3f input_vec, t_v3f normale)
{
	t_v3f	tmp;
	float	scalar;
	t_v3f	reflection_vec;

	v3f_copy(&reflection_vec, &input_vec);
	scalar = 2 * v3f_scalar_product(&input_vec, &normale);
	tmp = v3f_dot_scalar(&normale, scalar);
	v3f_minus_equal(&reflection_vec, &tmp);
	return (reflection_vec);
}

t_color	compute_specular_color(const t_ray *input_ray, const t_ray *normal_ray, const t_shape *shape, const t_light *light)
{
	t_color	c;
	float	dot;
	t_v3f	reflec;
	t_v3f	light_vec;
	float	alpha;
	float	k_s;

	alpha = 50.0f;
	k_s = 1.0f;
	(void)shape;
	c = color_create_int(0);
	light_vec = normal_ray->origin;
	v3f_minus_equal(&light_vec, &light->origin);
	v3f_normalize(&light_vec);
	reflec = compute_reflection_vector(light_vec, normal_ray->direction);
	dot = - v3f_scalar_product(&reflec, &input_ray->direction);
	if (dot < 0)
		return (c);
	dot = k_s * powf(dot, alpha);
	c = color_mult_c(light->color, dot * light->intensity);
	return (c);
}

t_ray	init_ray(t_scene *s, int x, int y)
{
	t_ray	r;
	float	scale;

	scale = tan(s->cam.fov / 2);
	v3f_copy(&r.origin, &s->cam.pos);

	r.direction.x = (2.0f * ((float)x + 0.5f) / (float)s->w - 1.0f) * s->ratio * scale;
	r.direction.y = -(2.0f * ((float)y + 0.5f) / (float)s->h - 1.0f) * scale;
	r.direction.z = 1.0f;
	r.direction.w = 0.0f;

	r.direction = cam2world(&s->cam, r.direction);
	v3f_normalize(&r.direction);
	return (r);
}

void	around(t_scene *scene, int x, int y, void *data)
{
	t_app	*app;
	app = (t_app *)data;
	t_color	c;
	t_ray	r;
	const t_shape	*shape;
	t_ray	normal_ray;

	r = init_ray(scene, x, y);

	if(x == app->scene.w / 2 && y == app->scene.h / 2)
	{
		printf("\x1b[36m");
		v3f_print(&scene->cam.orien);
		printf("\x1b[33m");
		v3f_print(&r.direction);
		printf("\x1b[0m" "\n");
	}

	c = color_create_int(0);
	shape = get_closest_shape(scene->shapes, &r, &normal_ray);
	if (shape)
	{
		if (shape->type == SPHERE)
		{
			c = color_mult_c(scene->ambient, scene->ambient_intensity);
			c = color_add(c, compute_normal_texture(&normal_ray, shape, &scene->textures[0]));
			c = color_add(c, color_mult_c(compute_normal_texture(&normal_ray, shape, &scene->textures[1]), 0.8));
			c = color_mult(c, (compute_diffuse_color(&normal_ray, shape, scene->lights, color_create_int(0xFFFFFFFF))));
			//c = color_mult(c, compute_chess_color(&normal_ray, shape));
		}
		else
		{
			c = color_mult_c(scene->ambient, scene->ambient_intensity);
			c = color_add(c, compute_diffuse_color(&normal_ray, shape, scene->lights, shape->color));
			c = color_mult(c, compute_chess_color(&normal_ray, shape));
			c = color_add(c, compute_specular_color(&r, &normal_ray, shape, scene->lights));
		}
	}
	app->pix_ptr[(int)(x + (y * scene->w))] = color_int(&c);
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
		mlx_clear_window(app->mlx_ptr, app->win_ptr);
		ft_memset(app->pix_ptr, 0, app->scene.w*app->scene.h*4);
		scene_around(&(app->scene), app, &around);
		mlx_put_image_to_window(app->mlx_ptr, app->win_ptr, app->img_ptr, 0, 0);
		app->on_change = 0;
	}

	return (0);
}

static int	init_mlx(t_app *app)
{
	int	bpp;
	int	endian;
	int	size_line;

	app->mlx_ptr = mlx_init();
	if (!app->mlx_ptr)
		return (1);
	app->win_ptr = mlx_new_window(app->mlx_ptr, app->scene.w, app->scene.h, "minirt");
	if (!app->win_ptr)
		return (2);
	app->img_ptr = mlx_new_image(app->mlx_ptr, app->scene.w, app->scene.h);
	if (!app->img_ptr)
		return (3);
	app->pix_ptr = (unsigned int *)mlx_get_data_addr(app->img_ptr, &bpp, &size_line, &endian);
	if (!app->pix_ptr)
		return (4);
	app->scene.textures = malloc(3 * sizeof(t_image));
	load_texture_xpm("textures/2k_earth_daymap.xpm", app->mlx_ptr, &app->scene.textures[0]);
	load_texture_xpm("textures/2k_earth_clouds.xpm", app->mlx_ptr, &app->scene.textures[1]);
	load_texture_xpm("textures/2k_earth_normal_map.xpm", app->mlx_ptr, &app->scene.textures[2]);
	mlx_hook(app->win_ptr, MLX_EVT_DESTROY, 0L, &on_close, app);
	mlx_hook(app->win_ptr, MLX_EVT_KEYUP, 2L, &key_up, app);
	mlx_loop_hook(app->mlx_ptr, &loop, app);
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
	if (init_mlx(&app))
		return (1);
	if (argc == 3 && !ft_strcmp(argv[2], "-e"))
	{
		loop(&app);
		export_ppm("export.ppm", &app);
	}
	else
		mlx_loop(app.mlx_ptr);
	return (0);
}
