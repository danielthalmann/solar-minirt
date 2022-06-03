/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 07:47:50 by trossel           #+#    #+#             */
/*   Updated: 2022/06/03 10:43:43 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"
t_v3f	cam2world(t_camera *c, t_v3f p)
{
	t_v3f v;

	v.x = c->right.x * p.x + c->up.x * p.y + c->orien.x * p.z;
	v.y = c->right.y * p.x + c->up.y * p.y + c->orien.y * p.z;
	v.z = c->right.z * p.x + c->up.z * p.y + c->orien.z * p.z;
	v.w = 0;
	return (v);

}

/* The if is here because of gimbal lock */
void	camera_update_orien(t_camera *c, t_v3f orien)
{
	v3f_copy(&c->orien, &orien);
	v3f_normalize(&c->orien);
	if (fabsf(c->orien.z) < 1e-6 && fabsf(c->orien.x) < 1e-6)
	{
		v3f_copy(&c->right, &(t_v3f){c->orien.y, 0, 0, 0});
		v3f_copy(&c->up, &(t_v3f){0, 0, c->orien.y, 0});
	}
	else
	{
		c->right =  v3f_cross_product(&(t_v3f){0, 1.0f, 0, 0}, &c->orien);
		c->up = v3f_cross_product(&c->orien, &c->right);
	}
	v3f_normalize(&c->right);
	v3f_normalize(&c->up);
}

