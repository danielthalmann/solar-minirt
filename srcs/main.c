/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 23:17:13 by dthalman          #+#    #+#             */
/*   Updated: 2022/06/09 13:24:09 by trossel          ###   ########.fr       */
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

#define TEX_CLOUD "textures/2k_earth_clouds.xpm"
#define TEX_EARTH "textures/2k_earth_daymap.xpm"
#define TEX_NORMAL "textures/2k_earth_normal_map.xpm"

int	on_close(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	free_app(app);
	exit(0);
}

static int	init_mlx(t_app *app)
{
	app->mlx = mlx_init();
	if (!app->mlx)
		return (1);
	app->win_ptr = mlx_new_window(
			app->mlx, app->scene.w, app->scene.h, "minirt");
	if (!app->win_ptr)
		return (2);
	if (new_image(app->mlx, &app->img, app->scene.w, app->scene.h))
		return (3);
	app->scene.textures = malloc(3 * sizeof(t_image));
	if (!app->scene.textures)
		return (4);
	load_texture_xpm(TEX_EARTH, app->mlx, &app->scene.textures[0]);
	load_texture_xpm(TEX_CLOUD, app->mlx, &app->scene.textures[1]);
	load_texture_xpm(TEX_NORMAL, app->mlx, &app->scene.textures[2]);
	mlx_hook(app->win_ptr, MLX_EVT_DESTROY, 0L, &on_close, app);
	mlx_hook(app->win_ptr, MLX_EVT_KEYUP, 2L, &key_up, app);
	mlx_loop_hook(app->mlx, &loop, app);
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
		return (not_enough_arguments());
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
		mlx_loop(app.mlx);
	return (0);
}
