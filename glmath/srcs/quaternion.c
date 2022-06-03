/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:43:40 by dthalman          #+#    #+#             */
/*   Updated: 2022/06/01 20:58:03 by dthalman         ###   ########.fr       */
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

	inv = qion_inverse(rot);
	ret = qion_product(rot, q);
	ret = qion_product(&ret, &inv);
	return (ret);
}

t_qion	qion_inverse(const t_qion *q)
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
