/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:30:34 by trossel           #+#    #+#             */
/*   Updated: 2022/05/19 16:05:23 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_scanf_conversion.h"
#include "libft.h"

#include <stdlib.h>

static void	skip_int(const char **str)
{
	if (**str == '-' || **str == '+')
		(*str)++;
	while (ft_isdigit(**str))
		(*str)++;
}

int	scan_int(const char **str, const t_conv_param *p, va_list val)
{
	int	*c;

	if (!ft_isdigit(**str) && **str != '-' && **str != '+')
		return (1);
	if (p->assign_suppression)
	{
		skip_int(str);
		return (0);
	}
	c = va_arg(val, int *);
	if (!c)
		return (0);
	*c = ft_atoi(*str);
	skip_int(str);
	return (1);
}
