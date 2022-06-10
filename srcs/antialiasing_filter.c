/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing_filter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:04:10 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 21:59:33 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "antialiasing.h"

#include <stdlib.h>
#include <math.h>

static void	init_mat_gaussian(t_filter2d *f, float sigma)
{
	int		pos[2];
	float	p;
	float	q;
	float	sum;

	pos[0] = 0;
	pos[1] = 0;
	q = 2.0 * sigma * sigma;
	sum = 0;
	while (pos[1] < f->n)
	{
		p = sqrtf(powf(pos[0] - f->rank, 2) + powf(pos[1] - f->rank, 2));
		f->mat[pos[1] * f->n + pos[0]] = (exp(-(p * p) / q)) / (M_PI * q);
		sum += f->mat[pos[1] * f->n + pos[0]];
		if (++pos[0] >= f->n && ++pos[1])
			pos[0] = 0;
	}
	pos[0] = 0;
	pos[1] = 0;
	while (pos[1] < f->n)
	{
		f->mat[pos[1] * f->n + pos[0]] /= sum;
		if (++pos[0] >= f->n && ++pos[1])
			pos[0] = 0;
	}
}

static void	init_mat_mean(t_filter2d *f)
{
	int		pos[2];
	float	val;

	pos[0] = 0;
	pos[1] = 0;
	val = 1.0f / (float)(f->n * f->n);
	while (pos[1] < f->n)
	{
		f->mat[pos[1] * f->n + pos[0]] = val;
		if (++pos[0] == f->n && ++pos[1])
			pos[0] = 0;
	}
}

int	init_filter(t_filter2d *f, t_filter2d_type type, int rank)
{
	if (!f)
		return (1);
	if (rank < 0)
		rank = -rank;
	f->rank = rank;
	f->n = 2 * f->rank + 1;
	f->mat = malloc(pow(f->n, 2) * sizeof(float));
	if (!f->mat)
		return (1);
	if (type == GAUSSIAN)
		init_mat_gaussian(f, 1.0f);
	else
		init_mat_mean(f);
	return (0);
}
