/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:35:29 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 21:24:02 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "antialiasing.h"
#include "ft_printf.h"
#include "main.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

static t_color	apply_filter_pixel(
		t_image *img, t_filter2d *f, int x, int y)
{
	t_color	in;
	t_color	out;
	int		idx[2];
	float	mat_val;
	int		count = 0;

	out = color_create_int(0);
	idx[0] = 0;
	idx[1] = 0;
	while (idx[1] < f->n)
	{
		in = get_image_color(img, x + idx[0] - f->rank, y + idx[0] - f->rank);
		mat_val = f->mat[idx[1] * f->n + idx[0]];
		out.r += mat_val * in.r;
		out.g += mat_val * in.g;
		out.b += mat_val * in.b;
		count++;
		if (++idx[0] >= f->n && ++idx[1])
			idx[0] = 0;
	}
	printf("count = %d\n", count);
	return (out);
}

void	apply_filter(t_image *input, t_image *output, t_filter2d *f)
{
	int		idx[2];
	t_color	c;
	
	idx[0] = 0;
	idx[1] = 0;
	while (idx[1] < input->h)
	{
		c = apply_filter_pixel(input, f, idx[0], idx[1]);
		set_image_color(output, idx[0], idx[1], c);
		if (++idx[0] >= input->w && ++idx[1])
			idx[0] = 0;
	}
}

int	image_filter(t_image *img, t_filter2d_type type, int rank)
{
	t_filter2d	filter;
	t_image		img2;

	if (init_filter(&filter, type, rank))
	{
		printf("cannot create filter\n");
		return (1);
	}
	if (new_image(img->mlx_ptr, &img2, img->w, img->h))
		return (1);
	printf("Filter created: r = %d, n = %d\n", filter.rank, filter.n);
	apply_filter(img, &img2, &filter);	
	free(filter.mat);
	ft_memcpy(img->c_ptr, img2.c_ptr, img->w * img->h * 4);
	mlx_destroy_image(img2.mlx_ptr, img2.img_ptr);
	return (0);
}
