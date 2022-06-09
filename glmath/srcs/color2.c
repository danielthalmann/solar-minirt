/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:02:04 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 10:03:49 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

/**
 * @brief Addition deux couleurs
 * 
 * @param c1 
 * @param c2 
 * @return t_color 
 */
t_color	color_add(t_color c1, t_color c2)
{
	t_color	c;

	c.r = c1.r + c2.r;
	c.g = c1.g + c2.g;
	c.b = c1.b + c2.b;
	color_check(&c);
	return (c);
}

/**
 * @brief soustraie c2 de c1
 * 
 * @param c1 
 * @param c2 
 * @return t_color 
 */
t_color	color_minus(t_color c1, t_color c2)
{
	t_color	c;

	c.r = c1.r - c2.r;
	c.g = c1.g - c2.g;
	c.b = c1.b - c2.b;
	color_check(&c);
	return (c);
}

/**
 * @brief multiplie la couleur c avec un float
 * 
 * @param c 
 * @param f 
 * @return t_color 
 */
t_color	color_mult_c(const t_color c, float f)
{
	t_color	c2;

	c2.r = c.r * f;
	c2.g = c.g * f;
	c2.b = c.b * f;
	color_check(&c2);
	return (c2);
}

/**
 * @brief multiplie la couleur c1 avec la couleur c2
 * 
 * @param c1 
 * @param c2 
 * @return t_color 
 */
t_color	color_mult(const t_color c1, const t_color c2)
{
	t_color	c3;

	c3.r = c1.r * c2.r;
	c3.g = c1.g * c2.g;
	c3.b = c1.b * c2.b;
	return (c3);
}

/**
 * @brief applique la valeur 1 - x sur toutes les couleur
 * 
 * @param vector 
 */
t_color	color_reverse(t_color c)
{
	t_color	c2;

	c2.r = 1 - c.r;
	c2.g = 1 - c.g;
	c2.b = 1 - c.b;
	return (c2);
}
