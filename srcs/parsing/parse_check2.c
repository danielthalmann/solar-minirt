/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 21:39:09 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 21:41:58 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"
#include "ft_printf.h"

#include <unistd.h>

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
