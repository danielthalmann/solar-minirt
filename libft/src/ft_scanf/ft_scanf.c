/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scanf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 08:02:16 by trossel           #+#    #+#             */
/*   Updated: 2022/05/19 16:04:41 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

#include "ft_scanf_conversion.h"
#include "libft.h"
#include "ft_printf.h"

static int	ft_vsscanf(const char *str, const char *format, va_list args)
{
	int	n_conv;

	n_conv = 0;
	while (*str && *format)
	{
		if (ft_is_white_space(*format))
		{
			while (ft_is_white_space(*str))
					str++;
			format++;
		}
		else if (*format != '%')
		{
			if (*(str++) != *(format++))
				break ;
		}
		else
		{
			format++;
			if (!ft_sscanf_conversion(&str, &format, args))
				break ;
			n_conv++;
		}
	}
	return (n_conv);
}

int	ft_sscanf(const char *str, const char *format, ...)
{
	int		n;
	va_list	args;

	va_start(args, format);
	n = ft_vsscanf(str, format, args);
	va_end(args);
	return (n);
}
