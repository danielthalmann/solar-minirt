/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 08:02:16 by trossel           #+#    #+#             */
/*   Updated: 2021/11/16 14:00:52 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

#include "ft_printf_conversion.h"
#include "libft.h"

static int	ft_vprintf(const char *format, va_list args)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (format[i])
	{
		if (format[i] != '%')
			i++;
		else
		{
			write(1, format, i);
			c += i;
			format += i + 1;
			i = 0;
			c += print_conversion(&format, args);
		}
	}
	if (i != 0)
		write(1, format, i);
	c += i;
	return (c);
}

int	ft_printf(const char *s, ...)
{
	int		c;
	va_list	format;

	va_start(format, s);
	c = ft_vprintf(s, format);
	va_end(format);
	return (c);
}
