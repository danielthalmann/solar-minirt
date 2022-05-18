/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glmath.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 10:40:24 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/18 17:09:35 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLMATH_H
# define GLMATH_H
# include <stdlib.h>
# include <math.h>
# include <stdio.h>

typedef float				t_c;
typedef struct s_vector4f
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_v4f;

typedef struct s_vector4f	t_v3f;
typedef struct s_vector4f	t_point3f;

typedef struct s_vector2f
{
	float	x;
	float	y;
}	t_v2f;

typedef struct s_point2
{
	int	x;
	int	y;
}	t_point;
typedef struct s_point2f
{
	float	x;
	float	y;
}	t_pointf;
typedef struct s_color
{
	t_c	r;
	t_c	g;
	t_c	b;
	t_c	a;
}	t_color;
typedef struct s_ray
{
	t_point3f	origin;
	t_v3f		direction;
}	t_ray;
typedef struct s_light
{
	t_point3f		origin;
	float			intensity;
	t_color			color;
	struct s_light	*next;
}	t_light;

t_v3f	*v3f_create(t_v3f *copy);
void	v3f_add(t_v3f *to, t_v3f *add);
void	v3f_sub(t_v3f *to, t_v3f *sub);
void	v3f_normalize(t_v3f *vector);
void	v3f_multi_by(t_v3f *vector, t_v3f *multi);
t_v3f	v3f_multi(t_v3f *vector, t_v3f *multi);
void	v3f_multi_v(t_v3f *vector, float value);
void	v3f_clear(t_v3f *vector);
void	v3f_copy(t_v3f *to, t_v3f *copy);
void	v3f_abs(t_v3f *vector);
void	v3f_print(t_v3f *vector);
float	v3f_dot(t_v3f *v1, t_v3f *v2);
float	v3f_dist(t_point3f *p1, t_point3f *p2);

t_color	*color_create(t_color *copy);
t_color	*color_create_int(int color);
int		color_int(t_color *color);
void	cpy_vector_to_color(t_color *color, t_v3f *v);

t_ray	*ray_create(t_ray *copy);
t_v3f	*ray_at(float pos, t_ray *ray);
void	ray_clear(t_ray *r);

/* Shapes */
typedef struct s_sphere
{
	t_point3f	origin;
	float		radius;
	t_color		color;
}	t_sphere;
typedef struct s_cylinder
{
	t_point3f	origin;
	t_v3f		normal;
	float		radius;
	float		height;
	t_color		color;
}	t_cylinder;
typedef struct s_plane
{
	t_point3f	origin;
	float		normal;
	t_color		color;
}	t_plane;
enum e_shapetype
{
	SPHERE,
	CYLINDER,
	PLANE
};
typedef struct s_shape
{
	enum e_shapetype	type;
	struct s_shape		*next;
	int					(*intersect)(t_ray *, void *, t_v3f *);
	t_v3f				(*normal_vector)(t_ray *, void *, t_v3f *);
	union {
		void		*shape;
		t_sphere	sphere;
		t_cylinder	cylinder;
		t_plane		plane;
	};
}	t_shape;

typedef struct s_scene
{
	int		w;
	int		h;
	t_color	ambiant;
	t_shape	*shapes;
	t_light	*lights;
}	t_scene;

int		sphere_intersect(t_ray *ray, void *sphere, t_v3f *intersection);
void	computeColorNormal(t_ray *ray, float dist, t_color *c, t_v3f *normal);

void	scene_around(t_scene *scene, void *data,
			void (*fn)(t_scene *, int, int, void *));

#endif
