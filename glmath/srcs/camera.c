/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 07:47:50 by trossel           #+#    #+#             */
/*   Updated: 2022/06/08 12:05:50 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

t_ray	camera_init_ray(t_scene *s, int x, int y)
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

t_v3f	look_at(const t_camera *cam, const t_scene *scene, int x, int y)
{
	t_v3f	left;
	t_v3f	up;
	t_v3f	cross;
	float	fov_ratio;
	float	half_fov;
	t_qion	qr;
	t_v3f	vector;

	v3f_copy(&vector, &scene->cam.orien);

	fov_ratio = cam->fov / (float)scene->w;
	half_fov = cam->fov / 2;

	v3f_set(&up, 0.0, 1.0, 0.0);
	v3f_set(&left, 1.0, 0.0, 0.0);

	qr = qion_rotation_angle(-half_fov + (x * fov_ratio), &up);
	vector = qion_rotation(&vector, &qr);
	v3f_normalize(&vector);

	cross = v3f_cross_product(&up, &vector);
	v3f_normalize(&cross);

	qr = qion_rotation_angle(-half_fov + ((y + ((float)(scene->w - scene->h) / 2)) * fov_ratio), &cross);
	vector = qion_rotation(&vector, &qr);

	v3f_normalize(&vector);
	return (vector);
}
