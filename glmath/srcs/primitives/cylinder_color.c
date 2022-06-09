/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:06:41 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 11:16:33 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

float	cylinder_color_mask(const t_ray *normale, const t_cylinder *cyl)
{
	(void)normale;
	(void)cyl;
	return (1.0f);
}

t_color	cylinder_color_normal(
	const t_ray *normale, const t_cylinder *cyl, float intensity)
{
	t_color	c;

	(void) normale;
	(void) cyl;
	(void) intensity;
	c = color_create_int(0);
	return (c);
}

t_color	cylinder_color_texture(
	const t_ray *normale, const t_cylinder *cyl, t_image *texture)
{
	t_color	c;

	(void) normale;
	(void) cyl;
	(void) texture;
	c = color_create_int(0);
	return (c);
}
