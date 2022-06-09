/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:47:50 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 11:48:52 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

/**
 * @brief Retourne un vecteur à partir du point (0,0,0) d'une valeur de 1
 *  exemple, avec le vecteur (2,0,0) on obtiendra (1,0,0)
 *
 * @param v
 */
void	v3f_normalize(t_v3f *vector)
{
	float	magnitude;

	magnitude = v3f_abs(vector);
	if (magnitude == 0.0f)
		return ;
	vector->x /= magnitude;
	vector->y /= magnitude;
	vector->z /= magnitude;
}

/**
 * @brief retourne la magnitude
 *
 * @param vector
 * @param sub
 */
float	v3f_abs(t_v3f *v)
{
	return (sqrtf(v->x * v->x + v->y * v->y + v->z * v->z));
}

/**
 * @brief retourne la distance entre deux vecteurs
 *
 * @param p1
 * @param p2
 * @return float
 */
float	v3f_dist(const t_point3f *p1, const t_point3f *p2)
{
	float	d;

	d = (p1->x - p2->x) * (p1->x - p2->x);
	d += (p1->y - p2->y) * (p1->y - p2->y);
	d += (p1->z - p2->z) * (p1->z - p2->z);
	return (sqrtf(d));
}

/**
 * @brief applique la valeur 1 - x sur tous les axes du vecteur
 * 
 * @param vector 
 */
void	v3f_invers(t_v3f *vector)
{
	vector->x = 1 - vector->x;
	vector->y = 1 - vector->y;
	vector->z = 1 - vector->z;
	vector->w = 0.0;
}
