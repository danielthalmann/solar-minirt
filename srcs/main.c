/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 23:17:13 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/30 11:08:12 by trossel          ###   ########.fr       */
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

int	on_close(void)
{
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

t_color	compute_diffuse_color(t_ray normal_ray, const t_shape *shape, const t_light *light)
{
	t_v3f	il;
	float	dot;
	t_color	c;

	c = color_create_int(0);
	v3f_copy(&il, &light->origin);
	v3f_minus_equal(&il, &normal_ray.origin);
	v3f_normalize(&il);
	dot = v3f_scalar_product(&normal_ray.direction, &il);
	dot *= light->intensity;
	if (dot < 0.0f)
	{
		if (shape->type == PLANE)
			dot = -dot;
		else
			return (c);
	}
	c = color_mult_c(shape->color, dot);
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
	k_s = 5.0f;
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

void around(t_scene *scene, int x, int y, void *data)
{
	t_app	*app;
	app = (t_app *)data;
	t_color	c;
	t_ray	r;
	const t_shape	*shape;
	t_ray normal_ray;

	r.origin.x = scene->cam.pos.x;
	r.origin.y = scene->cam.pos.y;
	r.origin.z = scene->cam.pos.z;


	r.direction.x = -1.0 + (2 * ((float)x / (float)scene->w));
<<<<<<< HEAD
	r.direction.y = 1.0 - (2 * ((float)y / (float)scene->w)) - ((float)(scene->w - scene->h) / (float)scene->w);
	r.direction.z = 1.0;
=======
	r.direction.y = -1.0 + (2 * ((float)y / (float)scene->w)) + ((float)(scene->w - scene->h) / (float)scene->w);
	r.direction.z = -1.0;
	r.direction.w = 0.0;

	//r.direction = qion_product(&q, &r.direction);

	//v3f_normalize(&r.direction);
	v3f_plus_equal(&r.direction, &scene->cam.orien);
>>>>>>> test camera
	v3f_normalize(&r.direction);

	c = color_create_int(0);
	shape = get_closest_shape(scene->shapes, &r, &normal_ray);
	if (shape)
	{
		c = color_mult_c(scene->ambient, scene->ambient_intensity);
		c = color_add(c, compute_diffuse_color(normal_ray, shape, scene->lights));
		c = color_add(c, compute_specular_color(&r, &normal_ray, shape, scene->lights));
	}
	app->pix_ptr[(int)(x + (y * scene->w))] = color_int(&c);
}

int	loop(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (!app)
		return (1);
	app->scene.lights->origin.x -= 1.0f;
	if (app->scene.lights->origin.x <= -10.0f)
		app->scene.lights->origin.x = 10.0f;

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

static int init_mlx(t_app *app)
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
	mlx_hook(app->win_ptr, MLX_EVT_DESTROY, 0L, &on_close, &app);
	mlx_hook(app->win_ptr, MLX_EVT_KEYUP, 2L, &key_up, &app);
	mlx_loop_hook(app->mlx_ptr, &loop, app);
	return (0);
}

int	main(int argc, char **argv)
{
	t_app	app;
	app.on_change = 1;
	app.rotate_camera = 0;

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
<<<<<<< HEAD
	if (init_mlx(&app))
		return (1);
	if (argc == 3 && !ft_strcmp(argv[2], "-e"))
	{
		scene_around(&(app.scene), &app, &around);
		export_ppm("export.ppm", &app);
	}
	else
		mlx_loop(app.mlx_ptr);
=======
	// return (0);					// <-	PROTIP: REMOVE THIS LINE TO SEGFAULT
									//		due to missing *func for objects
									//		plane and cylinder

	t_v3f o;
	o.x = 0.0;
	o.y = 0.0;
	o.z = 1.0;
	o.w = 0.0;
	app.scene.cam.degree_orien = TO_DEGRE * acosf( v3f_scalar_product( &o, &app.scene.cam.orien ) );
	v3f_normalize(&o);
	
	t_v3f angles = v3f_vtoangle(&app.scene.cam.orien, &o);
	v3f_print(&o);
	printf("\n");
	v3f_print(&app.scene.cam.orien);
	printf("\n");
	v3f_print(&angles);
	printf("\n");


	app.mlx_ptr = mlx_init();
	if (!app.mlx_ptr)
		return (0);
	app.win_ptr = mlx_new_window(app.mlx_ptr, app.scene.w, app.scene.h, "minirt");
	mlx_hook(app.win_ptr, MLX_EVT_DESTROY, 0L, &on_close, &app);
	mlx_hook(app.win_ptr, MLX_EVT_KEYUP, 2L, &key_up, &app);
	mlx_loop_hook(app.mlx_ptr, &loop, &app);


	mlx_loop(app.mlx_ptr);

>>>>>>> add quaternion
	return (0);
}
