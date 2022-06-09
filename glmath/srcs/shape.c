/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 09:21:29 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 09:26:29 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

void	init_shape(t_shape *s)
{
	if (!s)
		return ;
	s->next = NULL;
	s->intersect = NULL;
	s->color_mask = NULL;
	s->color_texture = NULL;
	s->type = SPHERE;
	s->color_normal = NULL;
	s->shininess = 50.0f;
	s->refl_coeff = 1.0f;
}
