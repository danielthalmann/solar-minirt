/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 23:17:13 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/18 10:25:12 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		key_down(int keycode, void *param)
{
	t_app	*app;
	app = (t_app *)param;
	(void)keycode;
	app->on_change = 1;
	return (0);
}

int		key_up(int keycode, void *param)
{
	t_app	*app;
	app = (t_app *)param;
	// printf("keycode : %d, %c, %d\n", keycode, keycode, KEY_Q);
	if (keycode == KEY_RIGHT)
		app->mandel.range_min.x += 0.1;
	if (keycode ==KEY_LEFT)
		app->mandel.range_min.x -= 0.1;
	if (keycode == KEY_DOWN)
		app->mandel.range_min.y += 0.1;
	if (keycode ==KEY_UP)
		app->mandel.range_min.y -= 0.1;
	if (keycode == KEY_A)
		app->mandel.zoom *= 1.15;
	if (keycode ==KEY_S)
		app->mandel.zoom /= 1.15;
	if (keycode == KEY_Y)
		app->mandel.max_iter += 10;
	if (keycode ==KEY_X)
		app->mandel.max_iter -= 10;
	app->on_change = 1;

	return (0);
}
