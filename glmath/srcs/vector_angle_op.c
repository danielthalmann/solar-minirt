/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_angle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:30:18 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 11:30:49 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

/**
 * @brief retourne un vecteur contenant les angles entre deux
 * vecteur en radian
 *
 * @param v1
 * @param v2
 * @return t_v3f
 */
t_v3f	v3f_vtoangle(const t_v3f *v1, const t_v3f *v2)
{
	t_v3f	angle;
	t_v3f	u;
	t_v3f	v;

	v3f_copy(&u, v1);
	v3f_copy(&v, v2);
	u.x = 0;
	v.x = 0;
	angle.x = TO_DEGRE * acosf(v3f_scalar_product(&u, &v));
	v3f_copy(&u, v1);
	v3f_copy(&v, v2);
	u.y = 0;
	v.y = 0;
	angle.y = TO_DEGRE * acosf(v3f_scalar_product(&u, &v));
	v3f_copy(&u, v1);
	v3f_copy(&v, v2);
	u.z = 0;
	v.z = 0;
	angle.z = TO_DEGRE * acosf(v3f_scalar_product(&u, &v));
	return (angle);
}

/**
 * @brief retourne l'angle horizontal du plan
 *
 * @param v
 * @return float
 */
float	v3f_horizontal(const t_v3f *v)
{
	return (atan2f(v->z, v->x));
}

/**
 * @brief retourne l'angle vertical du plan
 *
 * @param v
 * @return float
 */
float	v3f_vertical(const t_v3f *v)
{
	return (atan2f(v->y, v->z));
}
