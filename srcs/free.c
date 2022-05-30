/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:46:03 by trossel           #+#    #+#             */
/*   Updated: 2022/05/30 16:47:51 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"
#include "main.h"
#include "mlx.h"

static void	free_lights(t_light *l)
{
	t_light	*tmp;

	while (l)
	{
		tmp = l->next;
		free(l);
		l = tmp;
	}
}

static void	free_shapes(t_shape *s)
{
	t_shape	*tmp;

	while (s)
	{
		tmp = s->next;
		free(s);
		s = tmp;
	}
}

void	free_app(t_app *app)
{
	free_shapes(app->scene.shapes);
	free_lights(app->scene.lights);
	if (app->img_ptr)
		mlx_destroy_image(app->mlx_ptr, app->img_ptr);
	if (app->win_ptr)
		mlx_destroy_window(app->mlx_ptr, app->win_ptr);
	if (app->mlx_ptr)
		mlx_destroy_display(app->mlx_ptr);
}
