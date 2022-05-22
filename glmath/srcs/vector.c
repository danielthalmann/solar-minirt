/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 10:42:10 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/20 09:47:09 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

/**
 * @brief Création d'un nouveau vecteur
 *
 * @param copy
 * @return t_v3f*
 */
t_v3f	*v3f_create(t_v3f *copy)
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
 * @brief Addition de deux vecteurs
 *
 * @param vector
 * @param add
 */
void	v3f_plus_equal(t_v3f *vector, const t_v3f *add)
{
	vector->w += add->w;
	vector->x += add->x;
	vector->y += add->y;
	vector->z += add->z;
}

/**
 * @brief Effectue une division de v1 par v2. Le résultat est retourné
 *  par la fonction
 * 
 * @param v1 
 * @param v2 
 * @return t_v3f 
 */
t_v3f	v3f_division(const t_v3f *v1, const t_v3f *v2)
{
	t_v3f	res;

	res.x = v1->x - v2->x;
	res.y = v1->y - v2->y;
	res.z = v1->z - v2->z;
	res.w = v1->w - v2->w;
	return (res);
}

/**
 * @brief Addition de deux vecteurs sans modifier les vecteurs passés en
 * paramètres
 * 
 * @param vector 
 * @param add 
 * @return t_v3f 
 */
t_v3f	v3f_plus(const t_v3f *vector, const t_v3f *add)
{
	t_v3f	res;

	res.x = vector->x + add->x;
	res.y = vector->y + add->y;
	res.z = vector->z + add->z;
	res.w = vector->w + add->w;
	return (res);
}

/**
 * @brief Soustraction de deux vecteurs
 *
 * @param vector
 * @param sub
 */
void	v3f_minus_equal(t_v3f *vector, const t_v3f *sub)
{
	vector->w -= sub->w;
	vector->x -= sub->x;
	vector->y -= sub->y;
	vector->z -= sub->z;
}

/**
 * @brief Soustraction de deux vecteurs sans modifier les vecteurs passés en
 * paramètres
 * 
 * @param vector 
 * @param add 
 * @return t_v3f 
 */
t_v3f	v3f_minus(const t_v3f *vector, const t_v3f *add)
{
	t_v3f	res;

	res.x = vector->x - add->x;
	res.y = vector->y - add->y;
	res.z = vector->z - add->z;
	res.w = vector->w - add->w;
	return (res);
}

/**
 * @brief Retourne un vecteur à partir du point (0,0,0) d'une valeur de 1
 *  exemple, avec le vecteur (2,0,0) on obtiendra (1,0,0)
 *
 * @param v
 */
void	v3f_normalize(t_v3f *vector)
{
	float	magnitude;

	magnitude = sqrt((vector->x * vector->x)
			+ (vector->y * vector->y) + (vector->z * vector->z));
	vector->x /= magnitude;
	vector->y /= magnitude;
	vector->z /= magnitude;
}

/**
 * @brief Mutliplication de deux vecteurs
 *
 * @param vector
 * @param add
 */
float	v3f_scalar_product(const t_v3f *v1, const t_v3f *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_v3f	v3f_cross_product(const t_v3f *v1, const t_v3f *v2)
{
	t_v3f	res;

	res.x = v1->y * v2->z - v1->z * v2->y;
	res.y = v1->z * v2->x - v1->x * v2->z;
	res.z = v1->x * v2->y - v1->y * v2->x;
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
 * @brief 
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
	return (res);
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
void	v3f_copy(t_v3f *to, t_v3f *copy)
{
	to->w = copy->w;
	to->x = copy->x;
	to->y = copy->y;
	to->z = copy->z;
}

/**
 * @brief modifie les valeurs du vecteur en absolut
 *
 * @param vector
 * @param sub
 */
float	v3f_abs(t_v3f *v)
{
	return (v->x * v->x + v->y * v->y + v->z * v->z);
}

float	v3f_dist(const t_point3f *p1, const t_point3f *p2)
{
	float	d;

	d = (p1->x - p2->x) * (p1->x - p2->x);
	d += (p1->y - p2->y) * (p1->y - p2->y);
	d += (p1->z - p2->z) * (p1->y - p2->z);
	return (sqrt(d));
}

/**
 * @brief affiche dans la console les valeurs du vecteur
 *
 * @param vector
 * @param sub
 */
void	v3f_print(t_v3f *v)
{
	printf("(%f, %f, %f ,%f)", v->w, v->y, v->z, v->w);
}
