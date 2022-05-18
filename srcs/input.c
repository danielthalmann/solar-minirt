/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 23:17:13 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/18 16:19:49 by trossel          ###   ########.fr       */
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
	(void)keycode;
	app->on_change = 1;

	return (0);
}
