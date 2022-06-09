/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:12:48 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 11:19:21 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

#define ANG M_PI_4

float	sphere_color_mask(const t_ray *normale, const t_sphere *sphere)
{
	float		theta;
	float		phi;

	theta = acosf(normale->direction.y);
	phi = atan2f(normale->direction.x, normale->direction.z);
	theta = fmod(theta, ANG);
	phi = fmod(phi, ANG);
	if (phi < 0)
		phi += ANG;
	if ((theta < ANG / 2 && phi < ANG / 2)
		|| (theta >= ANG / 2 && phi >= ANG / 2))
		return (0.5f);
	(void)sphere;
	return (1.0f);
}

t_color	sphere_color_normal(
	const t_ray *normale, const t_sphere *sphere, float intensity)
{
	t_color	c;
	t_v3f	vect;

	vect = v3f_minus(&sphere->origin, &normale->origin);
	v3f_normalize(&vect);
	v3f_reverse(&vect);
	cpy_vector_to_color(&c, &vect);
	c = color_mult_c(c, intensity);
	return (c);
}

t_color	sphere_color_texture(
	const t_ray *normale, const t_sphere *sphere, t_image *texture)
{
	t_color	c;
	int		y;
	int		x;
	float	theta;
	float	phi;	

	(void) sphere;
	theta = acosf(normale->direction.y);
	phi = atan2f(normale->direction.x, normale->direction.z);
	y = abs((int)(theta * M_1_PI * texture->h));
	if (normale->direction.x < 0)
		x = abs((int)(phi * M_1_PI * texture->w / 2));
	else
		x = texture->w - (abs((int)(phi * M_1_PI * texture->w / 2)));
	c = texture->get_image_color(texture, x, y);
	return (c);
}
