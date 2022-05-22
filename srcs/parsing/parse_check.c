/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:33:43 by trossel           #+#    #+#             */
/*   Updated: 2022/05/20 17:04:43 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"
#include "ft_printf.h"

#include <unistd.h>

#define MSG_START "Error: %s: "
#define N_ELEM_ERR "missing %d elements\n"
#define COLOR_ERR "color components must be between 0 and 255 included.\n"
#define NEGATIVE_FLOAT_ERR "%s must be positive.\n"
#define OUTSIDE_RANGE_ERR "%s must be between %d and %d included.\n"
#define NULL_VECTOR_ERR "%s vector cannot be null\n"

int	parse_check_n_elem(int diff, const char *el)
{
	if (!diff)
		return (0);
	ft_fprintf(STDERR_FILENO, MSG_START, el);
	ft_fprintf(STDERR_FILENO, N_ELEM_ERR, diff);
	return (1);
}

int	parse_check_non_null_vector(t_v3f *v, const char *err_msg, const char *el)
{
	if (v3f_abs(v) != 0)
		return (0);
	ft_fprintf(STDERR_FILENO, MSG_START, el);
	ft_fprintf(STDERR_FILENO, NULL_VECTOR_ERR, err_msg);
	return (1);
}

int	parse_check_positive_float(float f, const char *err_msg, const char *el)
{
	if (f >= 0.0f)
		return (0);
	ft_fprintf(STDERR_FILENO, MSG_START, el);
	ft_fprintf(STDERR_FILENO, NEGATIVE_FLOAT_ERR, err_msg);
	return (1);
}

int	parse_check_valid_color(int color[3], const char *el)
{
	if (color[0] <= 255 && color[1] <= 255 && color[2] <= 255
		&& color[0] >= 0 && color[1] >= 0 && color[2] >= 0)
		return (0);
	ft_fprintf(STDERR_FILENO, MSG_START, el);
	ft_fprintf(STDERR_FILENO, COLOR_ERR);
	return (1);
}

// TODO: I should really support float in ft_printf
int	parse_check_in_range(float f, float r[2], const char *var, const char *el)
{
	if (f >= r[0] && f <= r[1])
		return (0);
	ft_fprintf(STDERR_FILENO, MSG_START, el);
	ft_fprintf(STDERR_FILENO, OUTSIDE_RANGE_ERR, var, (int)r[0], (int)r[1]);
	return (1);
}
