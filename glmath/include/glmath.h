/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glmath.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 10:40:24 by dthalman          #+#    #+#             */
/*   Updated: 2022/06/15 07:37:44 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLMATH_H
# define GLMATH_H

# include <stdlib.h>
# include <math.h>
# include <stdio.h>

# define TO_RADIAN	0.01745329251f
# define TO_DEGRE	57.2957795457f

typedef unsigned int		t_ui;
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
typedef t_v3f				t_matrix[3];

typedef struct s_referential
{
	t_point3f	p;
	t_matrix	b;
	t_matrix	i;
}	t_referential;

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

// vector.c
t_v3f	*v3f_create(const t_v3f *copy);
void	v3f_set(t_v3f *vector, float x, float y, float z);
void	v3f_clear(t_v3f *vector);
void	v3f_copy(t_v3f *to, const t_v3f *copy);
void	v3f_print(t_v3f *vector);

// vector_add_sub.c
void	v3f_plus_equal(t_v3f *to, const t_v3f *add);
t_v3f	v3f_plus(const t_v3f *to, const t_v3f *add);
void	v3f_minus_equal(t_v3f *to, const t_v3f *sub);
t_v3f	v3f_minus(const t_v3f *to, const t_v3f *sub);
t_v3f	v3f_minus_val(const t_v3f *vector, const float value);

// vector_scalar_op.c
t_v3f	v3f_dot_scalar(const t_v3f *vector, float value);
void	v3f_dot_equal_scalar(t_v3f *vector, float value);
t_v3f	v3f_div_scalar(const t_v3f *v1, float value);
void	v3f_div_equal_scalar(t_v3f *vector, float value);

// vector_product.c
float	v3f_scalar_product(const t_v3f *v1, const t_v3f *v2);
t_v3f	v3f_cross_product(const t_v3f *v1, const t_v3f *v2);

// vector_norm.c
void	v3f_normalize(t_v3f *vector);
float	v3f_abs(t_v3f *v);
float	v3f_dist(const t_point3f *p1, const t_point3f *p2);
void	v3f_reverse(t_v3f *vector);

// vector_angle.c
t_v3f	v3f_vtoangle(const t_v3f *v1, const t_v3f *v2);
float	v3f_horizontal(const t_v3f *v);
float	v3f_vertical(const t_v3f *v);

// Referentials
t_ray	ray_to_referential(const t_referential *ref, const t_ray *world_ray);
t_ray	ray_from_referential(const t_referential *ref, const t_ray *ref_ray);
void	referential_set_vec(t_referential *ref, t_v3f v, int idx);

t_qion	qion_create(const t_qion *copy);
void	qion_copy(t_qion *to, const t_qion *copy);
void	qion_clear(t_qion *q);
t_qion	qion_product(const t_qion *q1, const t_qion *q2);
t_qion	qion_euler_rotation(float x, float y, float z);
t_qion	qion_conjugate(const t_qion *q);
t_qion	qion_rotation(const t_qion *q, const t_qion *rot);
float	qion_norm(const t_qion *q);
void	qion_normalize(t_qion *q);
t_v3f	qion_rotation_angle(const float angle, const t_v3f *v);

t_color	color_create(t_color *copy);
t_color	color_create_int(t_ui color);
t_ui	color_int(t_color *color);
void	cpy_vector_to_color(t_color *color, t_v3f *v);
t_color	color_add(t_color c1, t_color c2);
t_color	color_minus(t_color c1, t_color c2);
void	color_check(t_color *c);
t_color	color_mult_c(const t_color c, float f);
t_color	color_mult(const t_color c1, const t_color c2);
t_color	color_reverse(t_color c);

t_ray	*ray_create(const t_ray *copy);
t_v3f	ray_at(float pos, const t_ray *ray);
void	ray_clear(t_ray *r);

/* image */
typedef struct s_image
{
	void			*mlx_ptr;
	void			*img_ptr;
	t_ui			*c_ptr;
	int				w;
	int				h;
	int				bpp;
	int				size_line;
	int				endian;
	int				bytes;
	struct s_color	(*get_image_color)(struct s_image *i, int x, int y);
}	t_image;

/* Shapes */
typedef struct s_sphere
{
	t_point3f	origin;
	float		radius;
}	t_sphere;
typedef struct s_cylinder
{
	t_referential	ref;
	float			radius;
	float			height;
}	t_cylinder;
typedef struct s_plane
{
	t_referential	ref;
}	t_plane;
typedef struct s_cone
{
	t_referential	ref;
	float			radius;
	float			height;
}	t_cone;

/* texture */
typedef struct s_texture
{
	struct s_texture	*next;
	t_image				image;
	char				*filename;
	float				u;
	float				v;
	float				alpha;
	int					loaded;
}	t_texture;

typedef enum e_shapetype
{
	SPHERE,
	CYLINDER,
	PLANE,
	CONE
}	t_shapetype;
typedef struct s_shape
{
	t_shapetype		type;
	struct s_shape	*next;
	t_color			color;
	t_texture		*texture[2];
	t_texture		*normal_map;
	int				tex_id[2];
	int				nm_id;
	char			draw_checker;
	float			shininess;
	float			refl_coeff;
	int				(*intersect)(const t_ray *, const void *, t_v3f *);
	void			(*normal_ray)(t_ray *, const void *);
	float			(*color_mask)(const t_ray *, const void *);
	struct s_color	(*color_normal)(const t_ray *r, const void *s, float i);
	struct s_color	(*color_texture)(const t_ray *r, const void *s, t_image *i);
	union {
		void		*shape;
		t_sphere	sphere;
		t_cylinder	cyl;
		t_plane		plane;
		t_cone		cone;
	};
}	t_shape;

typedef struct s_camera
{
	t_v3f	pos;
	t_v3f	orien;
	t_v3f	up;
	t_v3f	right;
	float	fov;
}	t_camera;

typedef struct s_scene
{
	int			w;
	int			h;
	float		ratio;
	t_color		ambient;
	float		ambient_intensity;
	t_shape		*shapes;
	t_light		*lights;
	t_camera	cam;
	t_texture	*textures;
	t_light		*current_light;
}	t_scene;

// Shapes functions
void	init_shape(t_shape *s);
float	compute_chess_color(
			t_ray *normal_ray, const t_shape *shape);
t_color	compute_normal_color(
			t_ray *normal_ray, const t_shape *shape, float intensity);
t_color	compute_normal_texture(
			t_ray *normal_ray, const t_shape *shape, t_image *textures);

// Sphere functions
int		sphere_intersect(const t_ray *r, const t_sphere *s, t_point3f *inter);
float	sphere_color_mask(const t_ray *normale, const t_sphere *sphere);
void	sphere_normal_ray(t_ray *normal, t_sphere *sphere);
t_color	sphere_color_normal(const t_ray *normale, const t_sphere *sphere,
			float intensity);
t_color	sphere_color_texture(const t_ray *normale, const t_sphere *sphere,
			t_image *texture);
void	sphere_print(const t_sphere *s);

// Plane functions
int		plane_intersect(const t_ray *r, const t_plane *p, t_point3f *inter);
float	plane_color_mask(const t_ray *normale, const t_plane *plane);
void	plane_normal_ray(t_ray *normal, t_plane *plane);
t_color	plane_color_normal(const t_ray *normale, const t_plane *plane,
			float intensity);
t_color	plane_color_texture(const t_ray *normale, const t_plane *plane,
			t_image *texture);
void	plane_print(const t_plane *p);

// Cylinder functions
int		cylinder_intersect(const t_ray *r, const t_cylinder *cyl,
			t_point3f *inter);
float	cylinder_color_mask(const t_ray *normale, const t_cylinder *cyl);
void	cylinder_normal_ray(t_ray *normale, t_cylinder *plane);
t_color	cylinder_color_normal(const t_ray *normale, const t_cylinder *cyl,
			float intensity);
t_color	cylinder_color_texture(const t_ray *normale, const t_cylinder *cyl,
			t_image *texture);
void	cylinder_print(const t_cylinder *cyl);

// Cone functions
int		cone_intersect(const t_ray *r, const t_cone *cone,
			t_point3f *inter);
float	cone_color_mask(const t_ray *normale, const t_cone *cone);
void	cone_normal_ray(t_ray *normale, t_cone *plane);
t_color	cone_color_normal(const t_ray *normale, const t_cone *cone,
			float intensity);
t_color	cone_color_texture(const t_ray *normale, const t_cone *cone,
			t_image *texture);
void	cone_print(const t_cone *cone);

void	computeColorNormal(t_ray *ray, float dist, t_color *c, t_v3f *normal);

t_ray	camera_init_ray(t_scene *s, int x, int y);
void	camera_update_orien(t_camera *c, t_v3f orien);
t_v3f	cam2world(t_camera *c, t_v3f p);
t_v3f	look_at(const t_camera *cam, const t_scene *scene, int x, int y);

// Scene functions
void	init_scene(t_scene *s);
void	scene_around(t_scene *scene, void *data,
			void (*fn)(t_scene *, int, int, void *));

// math
int		solve_quadratic(float a, float b, float c, float sol[2]);
void	inverse_matrix(const t_v3f	m[3], t_v3f inv[3]);
t_v3f	matrix_dot_v3f(const t_matrix m, const t_v3f *v);

#endif
