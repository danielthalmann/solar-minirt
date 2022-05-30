/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:03:04 by dthalman          #+#    #+#             */
/*   Updated: 2022/06/01 14:15:08 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>
# include <stdio.h>
# include "mlx.h"
# include "glmath.h"
# include "input.h"

# define MLX_EVT_KEYDN 2
# define MLX_EVT_KEYUP 3
# define MLX_EVT_DESTROY 17

typedef struct s_app
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				on_change;
	int				on_rotate;
	int				rotate_camera;
	unsigned int	*pix_ptr;
	t_scene			scene;
}	t_app;

void	free_app(t_app *app);
int		on_close(void *app);

void	around(t_scene *scene, int x, int y, void *data);

int		parse(t_scene *scene, char *filename);

void	print_scene(t_scene *s);
#endif
