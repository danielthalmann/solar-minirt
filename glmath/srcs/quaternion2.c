/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:53:16 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 11:02:41 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

/**
 * @brief effectue le produit de deux quaternion
 * 
 * @param q1 
 * @param q2 
 * @return t_qion 
 */
t_qion	qion_product(const t_qion *q1, const t_qion *q2)
{
	t_qion	q;

	q.w = q1->w * q2->w - q1->x * q2->x - q1->y * q2->y - q1->z * q2->z;
	q.x = q1->w * q2->x + q1->x * q2->w + q1->y * q2->z - q1->z * q2->y;
	q.y = q1->w * q2->y - q1->x * q2->z + q1->y * q2->w + q1->z * q2->x;
	q.z = q1->w * q2->z + q1->x * q2->y - q1->y * q2->x + q1->z * q2->w;
	return (q);
}

/**
 * @brief effectue une rotation a l'aide des quaternion
 * 
 * @param a 
 * @param rot 
 * @return t_qion 
 */
t_qion	qion_rotation(const t_qion *q, const t_qion *rot)
{
	t_qion	ret;
	t_qion	inv;

	inv = qion_conjugate(rot);
	ret = qion_product(rot, q);
	ret = qion_product(&ret, &inv);
	return (ret);
}

t_qion	qion_conjugate(const t_qion *q)
{
	t_qion	inv;

	inv = qion_create(q);
	inv.x *= -1;
	inv.y *= -1;
	inv.z *= -1;
	return (inv);
}

/**
 * @brief retourne la longueur du quaternion
 * 
 * @param q 
 * @return float 
 */
float	qion_norm(const t_qion *q)
{
	float	norm;

	norm = q->w * q->w + q->x * q->x + q->y * q->y + q->z * q->z;
	return (sqrt(norm));
}

/**
 * @brief Retourne un vecteur à partir du point (0,0,0) d'une valeur de 1
 *  exemple, avec le vecteur (2,0,0) on obtiendra (1,0,0)
 *
 * @param v
 */
void	qion_normalize(t_qion *q)
{
	float	n;

	n = qion_norm(q);
	q->w /= n;
	q->x /= n;
	q->y /= n;
	q->z /= n;
}
