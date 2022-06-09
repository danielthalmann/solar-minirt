/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:43:40 by dthalman          #+#    #+#             */
/*   Updated: 2022/06/09 11:02:39 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

/**
 * @brief Création d'un nouveau quaternion
 *
 * @param copy
 * @return t_v3f*
 */
t_qion	qion_create(const t_qion *copy)
{
	t_qion	q;

	if (copy != NULL)
		qion_copy(&q, copy);
	else
		qion_clear(&q);
	return (q);
}

/**
 * @brief met à zéro toutes les valeurs d'un quaternion
 * 
 * @param q 
 */
void	qion_clear(t_qion *q)
{
	v3f_clear(q);
}

/**
 * @brief recopie un quaternion
 * 
 * @param to 
 * @param copy 
 */
void	qion_copy(t_qion *to, const t_qion *copy)
{
	v3f_copy(to, copy);
}

/**
 * @brief Crée un quaternion de rotation
 * 
 * @return t_qion 
 */
t_qion	qion_euler_rotation(float x, float y, float z)
{
	float	c[4];
	float	s[4];
	t_qion	q;

	c[1] = cosf(y / 2);
	c[2] = cosf(z / 2);
	c[3] = cosf(x / 2);
	s[1] = sinf(y / 2);
	s[2] = sinf(z / 2);
	s[3] = sinf(x / 2);
	q.w = c[1] * c[2] * c[3] + s[1] * s[2] * s[3];
	q.x = c[1] * c[2] * s[3] - s[1] * s[2] * c[3];
	q.y = s[1] * c[2] * c[3] + c[1] * s[2] * s[3];
	q.z = c[1] * s[2] * c[3] - s[1] * c[2] * s[3];
	return (q);
}

t_v3f	qion_rotation_angle(const float angle, const t_v3f *v)
{
	float	sinus;
	float	cosinus;
	t_v3f	vr;

	sinus = sinf(angle / 2);
	cosinus = cosf(angle / 2);
	vr.x = v->x * sinus;
	vr.y = v->y * sinus;
	vr.z = v->z * sinus;
	vr.w = cosinus;
	return (vr);
}
