/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 10:42:10 by dthalman          #+#    #+#             */
/*   Updated: 2022/06/09 11:48:37 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

/**
 * @brief Création d'un nouveau vecteur
 *
 * @param copy
 * @return t_v3f*
 */
t_v3f	*v3f_create(const t_v3f *copy)
{
	t_v3f	*v;

	v = malloc(sizeof(t_v3f));
	if (copy != NULL)
		v3f_copy(v, copy);
	else
		v3f_clear(v);
	return (v);
}

/**
 * @brief Défini les valeurs contenu dans le vecteur
 *
 * @param vector
 * @param x
 * @param y
 * @param z
 */
void	v3f_set(t_v3f *vector, float x, float y, float z)
{
	vector->x = x;
	vector->y = y;
	vector->z = z;
	vector->w = 0.0;
}

/**
 * @brief met à zéro toute les valeurs d'un vecteur
 *
 * @param vector
 */
void	v3f_clear(t_v3f *vector)
{
	vector->w = 0;
	vector->x = 0;
	vector->y = 0;
	vector->z = 0;
}

/**
 * @brief copie les valeurs d'un vecteur dans un autre
 *
 * @param to
 * @param copy
 */
void	v3f_copy(t_v3f *to, const t_v3f *copy)
{
	to->w = copy->w;
	to->x = copy->x;
	to->y = copy->y;
	to->z = copy->z;
}

/**
 * @brief affiche dans la console les valeurs du vecteur
 *
 * @param vector
 * @param sub
 */
void	v3f_print(t_v3f *v)
{
	printf("(% 7f, % 7f, % 7f, % 7f)", v->w, v->x, v->y, v->z);
}
