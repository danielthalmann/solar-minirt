/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_scalar_op.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:34:51 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 11:44:06 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

/**
 * @brief Division d'un vecteurs par une valeur
 *
 * @param vector
 * @param value
 */
void	v3f_div_equal_scalar(t_v3f *vector, float value)
{
	vector->x /= value;
	vector->y /= value;
	vector->z /= value;
}

/**
 * @brief Effectue une division de v1 par value. Le résultat est retourné
 *
 * @param v1
 * @param value
 * @return t_v3f
 */
t_v3f	v3f_div_scalar(const t_v3f *v1, float value)
{
	t_v3f	res;

	res.x = v1->x / value;
	res.y = v1->y / value;
	res.z = v1->z / value;
	res.w = v1->w / value;
	return (res);
}

/**
 * @brief Mutliplication d'un vecteurs par une valeur
 *
 * @param vector
 * @param v
 */
void	v3f_dot_equal_scalar(t_v3f *vector, float value)
{
	vector->x *= value;
	vector->y *= value;
	vector->z *= value;
}

/**
 * @brief Effectue une multiplication de v1 par value. Le résultat est retourné
 *
 * @param v
 * @param val
 * @return t_v3f
 */
t_v3f	v3f_dot_scalar(const t_v3f *v, float val)
{
	t_v3f	res;

	res.x = v->x * val;
	res.y = v->y * val;
	res.z = v->z * val;
	res.w = 0;
	return (res);
}
