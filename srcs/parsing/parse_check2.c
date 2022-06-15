/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 21:39:09 by trossel           #+#    #+#             */
/*   Updated: 2022/06/15 11:33:37 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"
#include "ft_printf.h"
#include "libft.h"

#include <unistd.h>

int	parse_check_file_extension(const char *filename, const char *ext)
{
	size_t	len_file;
	size_t	len_ext;

	len_file = ft_strlen(filename);
	len_ext = ft_strlen(ext);
	if (len_file < len_ext)
		return (1);
	if (ft_strncmp(&filename[len_file - len_ext], ext, len_ext))
		return (1);
	return (0);
}

int	parse_check_scene(t_scene *s)
{
	if (!s->lights)
		ft_fprintf(STDERR_FILENO, "Warning: no light found.\n");
	if (!s->shapes)
		ft_fprintf(STDERR_FILENO, "Warning: no shapes found.\n");
	if (s->cam.fov < 0.0f)
	{
		ft_fprintf(STDERR_FILENO, "Error: missing camera line.\n");
		return (1);
	}
	if (s->ambient_intensity < 0.0f)
	{
		ft_fprintf(STDERR_FILENO, "Error: missing ambient light line.\n");
		return (1);
	}
	return (0);
}
