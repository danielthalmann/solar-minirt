/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 23:17:13 by dthalman          #+#    #+#             */
/*   Updated: 2022/06/01 14:45:30 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	key_down(int keycode, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	(void)keycode;
	app->on_change = 1;
	return (0);
}

int	key_up(int keycode, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (keycode == KEY_ESC)
		on_close(app);
	else if (keycode == KEY_1)
		app->rotate_camera = !app->rotate_camera;
	app->on_change = 1;
	return (0);
}
