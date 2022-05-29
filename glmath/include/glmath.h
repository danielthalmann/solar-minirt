/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glmath.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 10:40:24 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/27 17:12:39 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLMATH_H
# define GLMATH_H
# include <stdlib.h>
# include <math.h>
# include <stdio.h>

# define MATH_PI	3.14159265358979323846f
# define MATH_PI_2	1.57079632679489661923f
# define MATH_PI_4	0.785398163397448309616f
# define MATH_1_PI	0.318309886183790671538f
# define MATH_2_PI	0.636619772367581343076f
# define MATH_1_180	0.005555555555555555f
# define TO_RADIAN	0.01745329251f
# define TO_DEGRE	57.2957795457f

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
typedef struct s_vector4f	t_qion;
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
t_v3f	v3f_division(const t_v3f *v1, const t_v3f *v2);
t_v3f	v3f_division_val(const t_v3f *v1, float value);
void	v3f_plus_equal(t_v3f *to, const t_v3f *add);
t_v3f	v3f_plus(const t_v3f *to, const t_v3f *add);
void	v3f_minus_equal(t_v3f *to, const t_v3f *sub);
t_v3f	v3f_minus(const t_v3f *to, const t_v3f *sub);
void	v3f_normalize(t_v3f *vector);

float	v3f_scalar_product(const t_v3f *v1, const t_v3f *v2);
t_v3f	v3f_cross_product(const t_v3f *v1, const t_v3f *v2);
t_v3f	v3f_dot_scalar(const t_v3f *vector, float value);
void	v3f_dot_equal_scalar(t_v3f *vector, float value);
void	v3f_clear(t_v3f *vector);
void	v3f_copy(t_v3f *to, const t_v3f *copy);
float	v3f_abs(t_v3f *v);
void	v3f_print(t_v3f *vector);
float	v3f_dist(const t_point3f *p1, const t_point3f *p2);
t_v3f	v3f_vtoangle(const t_v3f *v1, const t_v3f *v2);

t_qion	qion_create(t_qion *copy);
void	qion_copy(t_qion *to, t_qion *copy);
void	qion_clear(t_qion *q);
t_qion	qion_product(t_qion *q1, t_qion *q2);
t_qion	qion_rotation(t_v3f n, float a);

t_color	color_create(t_color *copy);
t_color	color_create_int(int color);
int		color_int(t_color *color);
void	cpy_vector_to_color(t_color *color, t_v3f *v);

t_ray	*ray_create(t_ray *copy);
t_v3f	ray_at(float pos, t_ray *ray);
void	ray_clear(t_ray *r);

/* Shapes */
typedef struct s_sphere
{
	t_point3f	origin;
	float		radius;
}	t_sphere;
typedef struct s_cylinder
{
	t_point3f	origin;
	t_v3f		normal;
	float		radius;
	float		height;
}	t_cylinder;
typedef struct s_plane
{
	t_point3f	origin;
	t_v3f		normal;
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
	t_color				color;
	int					(*intersect)(t_ray *, void *, t_v3f *);
	void				(*normal_ray)(t_ray *, void *);
	union {
		void		*shape;
		t_sphere	sphere;
		t_cylinder	cyl;
		t_plane		plane;
	};
}	t_shape;

typedef struct s_camera
{
	t_v3f	pos;
	t_v3f	orien;
	float	fov;
	float	degree_orien;
}	t_camera;
typedef struct s_scene
{
	int			w;
	int			h;
	t_color		ambient;
	float		ambient_intensity;
	t_shape		*shapes;
	t_light		*lights;
	t_camera	cam;
}	t_scene;

// Sphere functions
int		sphere_intersect(t_ray *ray, t_sphere *sphere, t_point3f *intersection);
void	sphere_normal_ray(t_ray *normal, t_sphere *sphere);
void	sphere_print(t_sphere *s);

// Plane functions
int		plane_intersect(t_ray *ray, t_plane *plane, t_point3f *intersec);
void	plane_normal_ray(t_ray *normal, t_plane *plane);

// Cylinder functions
int		cylinder_intersect(t_ray *ray, t_cylinder *plane, t_point3f *intersec);
void	cylinder_normal_ray(t_ray *normal, t_cylinder *plane);

void	computeColorNormal(t_ray *ray, float dist, t_color *c, t_v3f *normal);

void	scene_around(t_scene *scene, void *data,
			void (*fn)(t_scene *, int, int, void *));

#endif
