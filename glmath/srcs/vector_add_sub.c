/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_add_sub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:26:52 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 11:28:04 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

/**
 * @brief Addition de deux vecteurs sans modifier les vecteurs passés en
 * paramètres
 *
 * @param vector
 * @param add
 * @return t_v3f
 */
t_v3f	v3f_plus(const t_v3f *vector, const t_v3f *add)
{
	t_v3f	res;

	res.x = vector->x + add->x;
	res.y = vector->y + add->y;
	res.z = vector->z + add->z;
	res.w = vector->w + add->w;
	return (res);
}

/**
 * @brief Addition de deux vecteurs
 *
 * @param vector
 * @param add
 */
void	v3f_plus_equal(t_v3f *vector, const t_v3f *add)
{
	vector->w += add->w;
	vector->x += add->x;
	vector->y += add->y;
	vector->z += add->z;
}

/**
 * @brief Soustraction de deux vecteurs sans modifier les vecteurs passés en
 * paramètres
 *
 * @param vector
 * @param add
 * @return t_v3f
 */
t_v3f	v3f_minus(const t_v3f *vector, const t_v3f *add)
{
	t_v3f	res;

	res.x = vector->x - add->x;
	res.y = vector->y - add->y;
	res.z = vector->z - add->z;
	res.w = vector->w - add->w;
	return (res);
}

/**
 * @brief Soustraction de deux vecteurs
 *
 * @param vector
 * @param sub
 */
void	v3f_minus_equal(t_v3f *vector, const t_v3f *sub)
{
	vector->w -= sub->w;
	vector->x -= sub->x;
	vector->y -= sub->y;
	vector->z -= sub->z;
}
