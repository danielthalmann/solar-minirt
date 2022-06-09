/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_product.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:41:17 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 11:46:53 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

/**
 * @brief Produit scalaire de deux vecteurs correspond a |ab| . |cd|
 *
 * @param v1
 * @param v2
 *
 * @return Produit scalaire
 */
float	v3f_scalar_product(const t_v3f *v1, const t_v3f *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

/**
 * @brief Produit vectoriel de deux vecteurs v1 x v2.
 *
 * @param v1
 * @param v2
 *
 * @return Produit vectoriel. Ce vecteur est perpendiculaire à v1 et v2.
 */
t_v3f	v3f_cross_product(const t_v3f *v1, const t_v3f *v2)
{
	t_v3f	res;

	res.x = v1->y * v2->z - v1->z * v2->y;
	res.y = v1->z * v2->x - v1->x * v2->z;
	res.z = v1->x * v2->y - v1->y * v2->x;
	res.w = 0;
	return (res);
}
