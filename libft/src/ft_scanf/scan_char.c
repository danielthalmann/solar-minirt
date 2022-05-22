/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:30:34 by trossel           #+#    #+#             */
/*   Updated: 2022/05/19 15:30:08 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_scanf_conversion.h"
#include "libft.h"

#include <stdlib.h>

int	scan_char(const char **str, const t_conv_param *p, va_list val)
{
	char	*c;
	char	**ptr;

	if (p->assign_suppression)
	{
		(*str)++;
		return (0);
	}
	if (p->call_malloc)
	{
		ptr = va_arg(val, char **);
		if (!ptr)
			return (0);
		*ptr = malloc(sizeof(char));
		if (!*ptr)
			return (0);
		(*ptr)[0] = **str;
	}
	else
	{
		c = va_arg(val, char *);
		*c = **str;
	}
	(*str)++;
	return (1);
}
