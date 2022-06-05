/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:03:04 by dthalman          #+#    #+#             */
/*   Updated: 2022/06/08 11:43:00 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>
# include <stdio.h>
# include "mlx.h"
# include "glmath.h"
# include "input.h"
#include "gfx.h"

# define MLX_EVT_KEYDN 2
# define MLX_EVT_KEYUP 3
# define MLX_EVT_DESTROY 17

typedef struct s_app
{
	t_gfx_ctx		*gfx_ctx;
	t_img			*img;
	t_win			*win;
	int				on_change;
	int				on_rotate;
	int				rotate_camera;
	t_scene			scene;
}	t_app;

void	free_app(t_app *app);
int		on_close(void *app);

void	around(t_scene *scene, int x, int y, void *data);

int		parse(t_scene *scene, char *filename);

void	print_scene(t_scene *s);

t_color	get_image_color(struct s_image *i, int x, int y);
void	load_texture_xpm(char *filename, void *mlx_ptr, t_image *image);

char	get_light_ray(t_point3f *p, t_light *l, t_shape *shapes);
const t_shape	*get_closest_shape(const t_shape *s, const t_ray *input_ray,
			t_ray *normal);
t_color	compute_diffuse_color(t_ray *normal_ray, const t_shape *shape,
			const t_light *light, const t_color color);
t_color	compute_specular_color(const t_ray *input_ray, const t_ray *normal_ray,
			const t_shape *shape, const t_light *light);
#endif
