/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 10:42:10 by dthalman          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/05/25 23:29:58 by trossel          ###   ########.fr       */
=======
/*   Updated: 2022/05/31 08:56:18 by dthalman         ###   ########.fr       */
>>>>>>> quaternion is the base
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

	res.x = v1->x / v2->x;
	res.y = v1->y / v2->y;
	res.z = v1->z / v2->z;
	res.w = v1->w / v2->w;
	return (res);
}

/**
 * @brief Effectue une division de v1 par value. Le résultat est retourné
 *
 * @param v1
 * @param value
 * @return t_v3f
 */
t_v3f	v3f_division_val(const t_v3f *v1, float value)
{
	t_v3f	res;

	res.x = v1->x / value;
	res.y = v1->y / value;
	res.z = v1->z / value;
	res.w = v1->w / value;
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

	magnitude = v3f_abs(vector);
	if (magnitude == 0.0f)
		return ;
	vector->x /= magnitude;
	vector->y /= magnitude;
	vector->z /= magnitude;
}

/**
 * @brief Produit scalaire de deux vecteurs correspond a |ab| . |cd|
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
void	v3f_copy(t_v3f *to, const t_v3f *copy)
{
	to->w = copy->w;
	to->x = copy->x;
	to->y = copy->y;
	to->z = copy->z;
}

/**
 * @brief retourne la magnitude
 *
 * @param vector
 * @param sub
 */
float	v3f_abs(t_v3f *v)
{
	return (sqrtf(v->x * v->x + v->y * v->y + v->z * v->z));
}

/**
 * @brief retourne la distance entre deux vecteurs
 *
 * @param p1
 * @param p2
 * @return float
 */
float	v3f_dist(const t_point3f *p1, const t_point3f *p2)
{
	float	d;

	d = (p1->x - p2->x) * (p1->x - p2->x);
	d += (p1->y - p2->y) * (p1->y - p2->y);
	d += (p1->z - p2->z) * (p1->z - p2->z);
	return (sqrtf(d));
}

/**
 * @brief affiche dans la console les valeurs du vecteur
 *
 * @param vector
 * @param sub
 */
void	v3f_print(t_v3f *v)
{
	printf("(%f, %f, %f, %f)", v->w, v->x, v->y, v->z);
}

/**
 * @brief retourne un vecteur contenant les angles entre deux
 * vecteur en radian
 * 
 * @param v1 
 * @param v2 
 * @return t_v3f 
 */
t_v3f	v3f_vtoangle(const t_v3f *v1, const t_v3f *v2)
{
	t_v3f	angle;
	t_v3f	u;
	t_v3f	v;

	v3f_copy(&u, v1);
	v3f_copy(&v, v2);
	u.x = 0;
	v.x = 0;
	angle.x = TO_DEGRE * acosf( v3f_scalar_product( &u, &v ) );
	v3f_copy(&u, v1);
	v3f_copy(&v, v2);
	u.y = 0;
	v.y = 0;
	angle.y = TO_DEGRE * acosf( v3f_scalar_product( &u, &v ) );
	v3f_copy(&u, v1);
	v3f_copy(&v, v2);
	u.z = 0;
	v.z = 0;
	angle.z = TO_DEGRE * acosf( v3f_scalar_product( &u, &v ) );
	return (angle);
}

float	v3f_horizontal(const t_v3f *v)
{
	t_v3f	u;

	v3f_copy(&u, v);
	u.y = 0;
	v3f_normalize(&u);
	return atanf(u.x / u.z);
}

float	v3f_vertical(const t_v3f *v)
{
	t_v3f	u;

	v3f_copy(&u, v);
	u.x = 0;
	v3f_normalize(&u);
	return atanf(u.z / u.y);
}
