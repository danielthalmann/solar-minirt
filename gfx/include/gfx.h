/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:45:07 by trossel           #+#    #+#             */
/*   Updated: 2022/06/05 10:39:35 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###############
// # GFX Context #
// ###############

typedef void t_gfx_ctx;

t_gfx_ctx	*gfx_init(void);

// ##########
// # Window #
// ##########

typedef struct s_win
{
	void	*mlx_win;
	int		w;
	int		h;
	char	*title;
	void	*ctx;
}	t_win;

t_win	*win_init(t_gfx_ctx *ctx, int w, int h, char *t);
void	win_free(t_win **win);
void	win_clear(t_win *win);

// #########
// # Image #
// #########

typedef struct s_img
{
	int					w;
	int					h;
	void				*mlx_img;
	unsigned int		*pixels;
	int					bpp;
	int					line_size;
	int					endian;
	t_gfx_ctx			*ctx;
}	t_img;


t_img	*img_init(t_gfx_ctx *ctx, int w, int h);
t_img	*img_from_xpm_file(t_gfx_ctx *ctx, char *str);
int		img_get_pixel(t_img *img, int x, int y);
void	img_set_pixel(t_img *img, int x, int y, int c);
void	img_free(t_img **img);
void	img_clear(t_img *img);
void	img_draw_to_win(t_img * img, t_win *win, int x, int y);

// ########
// # Loop #
// ########
