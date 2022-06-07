/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:33:13 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/30 08:12:40 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

/**
 * @brief Création d'un nouveau vecteur
 *
 * @param copy
 * @return color*
 */
t_color	color_create(t_color *copy)
{
	t_color	c;

	if (copy != NULL)
	{
		c.a = copy->a;
		c.r = copy->r;
		c.g = copy->g;
		c.b = copy->b;
	}
	else
	{
		c.a = 0;
		c.r = 0;
		c.g = 0;
		c.b = 0;
	}
	return (c);
}

/**
 * @brief Création d'une couleur avec un entier
 *
 * @param color
 * @return t_color*
 */
t_color	color_create_int(t_ui color)
{
	t_color	c;

	c.b = (color & 0xFF) / 255.0;
	c.g = ((color >> 8) & 0xFF) / 255.0;
	c.r = ((color >> 16) & 0xFF) / 255.0;
	c.a = ((color >> 24) & 0xFF) / 255.0;
	return (c);
}

/**
 * @brief retourne la valeur représenté par la couleur
 * en entier
 *
 * @param color
 * @return int
 */
t_ui	color_int(t_color *color)
{
	t_ui	c;

	c = 0;
	c += (int)(color->a * 255.0) & 0xFF;
	c = c << 8;
	c += (int)(color->r * 255.0) & 0xFF;
	c = c << 8;
	c += (int)(color->g * 255.0) & 0xFF;
	c = c << 8;
	c += (int)(color->b * 255.0) & 0xFF;
	return (c);
}

/**
 * @brief converti un vecteur en couleur
 *
 * @param color
 * @param v
 */
void	cpy_vector_to_color(t_color *color, t_v3f *v)
{
	color->r = v->x;
	color->g = v->y;
	color->b = v->z;
	color->a = v->w;
}

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
 * @brief normalise les valeurs r g b pour qu'elles ne dépassement pas 
 * les limites de la couleur
 * 
 * @param c 
 */
void	color_check(t_color *c)
{
	if (c->r > 1.0f)
		c->r = 1.0f;
	else if (c->r < 0.0f)
		c->r = 0.0f;
	if (c->g > 1.0f)
		c->g = 1.0f;
	else if (c->g < 0.0f)
		c->g = 0.0f;
	if (c->b > 1.0f)
		c->b = 1.0f;
	else if (c->b < 0.0f)
		c->g = 0.0f;
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