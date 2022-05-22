/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:20:30 by trossel           #+#    #+#             */
/*   Updated: 2022/05/19 15:17:27 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static float	check_sign(const char **str)
{
	float	sign;

	sign = 1.0f;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-' && ft_isdigit(*(*str + 1)))
			sign = -1.0f;
		(*str)++;
	}
	return (sign);
}

/*
 * WARNING: is not as precise as the real atof !! There are some differences
 * for the __last__ precision digit.
 * Which is for me good enough for the moment.
 *
 * */
float	ft_atof(const char *str)
{
	float	f;
	float	n_divider;
	float	sign;

	f = 0.0f;
	while (ft_is_white_space(*str))
		str++;
	sign = check_sign(&str);
	while (ft_isdigit(*str))
	{
		f *= 10;
		f += *(str++) - '0';
	}
	if (*str++ != '.')
		return (sign * f);
	n_divider = 1;
	while (ft_isdigit(*str))
	{
		f *= 10;
		f += *(str++) - '0';
		n_divider *= 10;
	}
	return (sign * f / n_divider);
}
