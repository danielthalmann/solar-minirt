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
    float c1 = cosf(y/2);
    float c2 = cosf(z/2);
    float c3 = cosf(x/2);

    float s1 = sinf(y/2);
    float s2 = sinf(z/2);
    float s3 = sinf(x/2);
    t_qion q;
    q.w = c1 * c2 * c3 + s1 * s2 * s3;
    q.x = c1 * c2 * s3 - s1 * s2 * c3;
    q.y = s1 * c2 * c3 + c1 * s2 * s3;
    q.z = c1 * s2 * c3 - s1 * c2 * s3;
    return q;
}

/**
 * @brief effectue une rotation a l'aide des quaternion
 * 
 * @param a 
 * @param rot 
 * @return t_qion 
 */
t_qion	qion_rotation2(const t_qion *q, const t_qion *rot)
{
	t_qion	ret;
	t_qion	inv;
	t_qion	norm;

	qion_copy(&norm, rot);
	qion_normalize(&norm);
	inv = qion_inverse(&norm);
	ret = qion_product(rot, q);
	ret = qion_product(&ret, &inv);
	return (ret);
}

t_qion	qion_rotation(const t_qion *point, const t_qion *rotation)
{
	float x = rotation->x * 2.0f;
	float y = rotation->y * 2.0f;
	float z = rotation->z * 2.0f;
	float xx = rotation->x * x;
	float yy = rotation->y * y;
	float zz = rotation->z * z;
	float xy = rotation->x * y;
	float xz = rotation->x * z;
	float yz = rotation->y * z;
	float wx = rotation->w * x;
	float wy = rotation->w * y;
	float wz = rotation->w * z;

	t_qion res;
	res.w = 0.0f;
	res.x = (1.0f - (yy + zz)) * point->x + (xy - wz) * point->y + (xz + wy) * point->z;
	res.y = (xy + wz) * point->x + (1.0f - (xx + zz)) * point->y + (yz - wx) * point->z;
	res.z = (xz - wy) * point->x + (yz + wx) * point->y + (1.0f - (xx + yy)) * point->z;
	
	return res;
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

float	qion_norm(const t_qion *q)
{
	float norm = q->w * q->w + q->x * q->x + q->y * q->y + q->z * q->z;
	return sqrt(norm);
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