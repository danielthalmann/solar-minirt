/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 23:17:13 by dthalman          #+#    #+#             */
/*   Updated: 2022/06/13 18:59:19 by trossel          ###   ########.fr       */
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
	mlx_hook(app->win_ptr, MLX_EVT_DESTROY, 0L, &on_close, app);
	mlx_hook(app->win_ptr, MLX_EVT_KEYUP, 2L, &key_up, app);
	mlx_loop_hook(app->mlx, &loop, app);
	return (0);
}

void	init_app(t_app *app)
{
	init_scene(&app->scene);
	app->on_change = 1;
	app->rotate_camera = 1;
	app->scene.ratio = 16.0 / 9.0;
	app->scene.h = 480;
	app->scene.w = app->scene.h * app->scene.ratio;
}

int	main(int argc, char **argv)
{
	t_app	app;

	init_app(&app);
	if (argc < 2)
		return (not_enough_arguments());
	if (parse(&app.scene, argv[1]))
		return (1);
	if (init_mlx(&app))
		return (1);
	init_texture(&app);
	if (argc == 3 && !ft_strcmp(argv[2], "-e"))
	{
		loop(&app);
		export_ppm("export.ppm", &app);
	}
	else
		mlx_loop(app.mlx);
	return (0);
}
