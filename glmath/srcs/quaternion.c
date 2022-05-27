/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:43:40 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/27 15:43:40 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"


/**
 * @brief Création d'un nouveau quaternion
 *
 * @param copy
 * @return t_v3f*
 */
t_qion	qion_create(t_qion *copy)
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
void	qion_copy(t_qion *to, t_qion *copy)
{
	v3f_copy(to, copy);
}

/**
 * @brief effectue le produit de deux quaternion
 * 
 * @param q1 
 * @param q2 
 * @return t_qion 
 */
t_qion	qion_product(t_qion *q1, t_qion *q2)
{
	t_qion	q;

	q.w = q1->w * q2->w - q1->x * q2->x - q1->y * q2->y - q1->z * q2->z;
	q.x = q1->w * q2->x + q1->x * q2->w + q1->y * q2->z - q1->z * q2->y;
	q.y = q1->w * q2->y - q1->x * q2->z + q1->y * q2->w + q1->z * q2->x;
	q.z = q1->w * q2->z + q1->x * q2->y - q1->y * q2->x + q1->z * q2->w;
	return (q);
}

/**
 * @brief Crée un quaternion de rotation
 * 
 * @param n normal utilisé pour la rotation
 * @param a angle de rotation en degré
 * @return t_qion 
 */
t_qion	qion_rotation(t_v3f n, float a)
{
	t_qion	q;

	q = qion_create(&n);
	q.w = cosf(a * TO_RADIAN / 2);
	q.x *= sinf(a * TO_RADIAN / 2);
	q.y *= sinf(a * TO_RADIAN / 2);
	q.z *= sinf(a * TO_RADIAN / 2);
	return (q);
}
