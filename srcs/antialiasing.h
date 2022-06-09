/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:05:07 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 22:36:13 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANTIALIASING_H
# define ANTIALIASING_H

# include "glmath.h"

typedef enum e_filter2d_type
{
	MEAN,
	GAUSSIAN
}	t_filter2d_type;

typedef struct s_filter2d
{
	int		rank;
	int		n;
	float	*mat;
}	t_filter2d;

int	init_filter(t_filter2d *f, t_filter2d_type type, int rank);

int	image_filter(t_image *img, t_filter2d_type type, int rank);

#endif
