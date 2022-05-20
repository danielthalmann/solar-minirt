/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 19:49:48 by trossel           #+#    #+#             */
/*   Updated: 2022/06/07 14:10:23 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"
#include <math.h>

void	inverse_matrix(const t_v3f	m[3], t_v3f inv[3])
{
	float	det;

	det = m[0].x*m[1].y*m[2].z + m[0].y*m[1].z*m[2].x + m[0].z*m[1].x*m[2].y
		- m[0].x*m[1].z*m[2].y - m[0].y*m[1].x*m[2].z - m[0].z*m[1].y*m[2].x;
	inv[0].x = (m[1].y*m[2].z - m[1].z*m[2].y)/det;
	inv[0].y = (m[0].z*m[2].y - m[0].y*m[2].z)/det;
	inv[0].z = (m[0].y*m[1].z - m[0].z*m[1].y)/det;
	inv[1].x = (m[1].z*m[2].x - m[1].x*m[2].z)/det;
	inv[1].y = (m[0].x*m[2].z - m[0].z*m[2].x)/det;
	inv[1].z = (m[0].z*m[1].x - m[0].x*m[1].z)/det;
	inv[2].x = (m[1].x*m[2].y - m[1].y*m[2].x)/det;
	inv[2].y = (m[0].y*m[2].x - m[0].x*m[2].y)/det;
	inv[2].z = (m[0].x*m[1].y - m[0].y*m[1].x)/det;
}

t_v3f	matrix_dot_v3f(const t_v3f	m[3], const t_v3f *v)
{
	t_v3f	v2;

	v2.x = m[0].x * v->x + m[1].x * v->y * m[2].x * v->z;
	v2.y = m[0].y * v->x + m[1].y * v->y * m[2].y * v->z;
	v2.z = m[0].z * v->x + m[1].z * v->y * m[2].z * v->z;
	return (v2);
}

int	solve_quadratic(float a, float b, float c, float sol[2])
{
	float	disc;

	disc = b * b - 4 * a * c;
	if (disc < 0)
	{
		sol[0] = NAN;
		sol[1] = NAN;
		return (0);
	}
	if (fabsf(disc) < 1e-6)
	{
		sol[0] = -b / (2 * a);
		sol[1] = sol[0];
		return (1);
	}
	disc = sqrtf(disc);
	sol[0] = (-b - disc) / (2 * a);
	sol[1] = (-b + disc) / (2 * a);
	return (2);
}
