/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_ppm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:09:27 by trossel           #+#    #+#             */
/*   Updated: 2022/05/30 08:33:06 by trossel          ###   ########.fr       */
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

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ptr = (unsigned char *)&color;
	if (fd < 0)
	{
		ft_fprintf(STDERR_FILENO, "Error: Could not open PPM\n");
		return (1);
	}
	ft_fprintf(STDERR_FILENO, "Info: starting export to: %s\n", filename);
	ft_fprintf(fd, "P3\n%d %d\n255\n", app->scene.w, app->scene.h);
	i = -1;
	while (++i < app->scene.w * app->scene.h)
	{
		color = app->pix_ptr[i];
		ft_fprintf(fd, "%d %d %d\n", ptr[2], ptr[1], ptr[0]);
	}
	close(fd);
	ft_fprintf(STDERR_FILENO, "Info: exported image to PPM file: %s\n",
		filename);
	return (0);
}
