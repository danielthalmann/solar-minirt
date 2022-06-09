/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_ppm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:09:27 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 13:25:12 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "main.h"
#include "ft_printf.h"

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
		ft_printf("\rExport to PPM: %d %%", i * 100 / n_pixels);
	}
	ft_printf("\rExport to PPM: 100%%\n");
	close(fd);
	return (0);
}
