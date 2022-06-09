/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_ppm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:09:27 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 17:58:32 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "main.h"
#include "ft_printf.h"

void	show_progress(const char *str, int i, int n_pixels)
{
	static int	perc = -1;
	int			new_perc;

	new_perc = i * 100 / n_pixels + 1;
	if (new_perc == perc)
		return ;
	perc = new_perc;
	ft_printf(str, i * 100 / n_pixels);
}

int	export_ppm(char	*filename, t_app *app)
{
	int				fd;
	int				i;
	int				color;
	unsigned char	*ptr;
	int				n_pixels;

	n_pixels = app->scene.w * app->scene.h;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ptr = (unsigned char *)&color;
	if (fd < 0)
	{
		ft_fprintf(STDERR_FILENO, "Error: Could not open PPM\n");
		return (1);
	}
	ft_fprintf(fd, "P3\n%d %d\n255\n", app->scene.w, app->scene.h);
	i = -1;
	while (++i < app->scene.w * app->scene.h)
	{
		color = app->img.c_ptr[i];
		ft_fprintf(fd, "%d %d %d\n", ptr[2], ptr[1], ptr[0]);
		show_progress("\rExport to PPM: %d %%", i, n_pixels);
	}
	close(fd);
	return (0);
}
