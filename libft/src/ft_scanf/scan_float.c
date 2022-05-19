/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_float.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:20:49 by trossel           #+#    #+#             */
/*   Updated: 2022/05/19 16:05:16 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_scanf_conversion.h"
#include "libft.h"

static void	skip_float(const char **str)
{
	if (**str == '-' || **str == '+')
		(*str)++;
	while (ft_isdigit(**str))
		(*str)++;
	if (**str != '.')
		return ;
	else
		(*str)++;
	while (ft_isdigit(**str))
		(*str)++;
}

int	scan_float(const char **str, const t_conv_param *p, va_list val)
{
	float	*c;

	if (!ft_isdigit(**str) && **str != '-' && **str != '+')
		return (1);
	if (p->assign_suppression)
	{
		skip_float(str);
		return (0);
	}
	c = va_arg(val, float *);
	if (!c)
		return (0);
	*c = ft_atof(*str);
	skip_float(str);
	return (1);
}
