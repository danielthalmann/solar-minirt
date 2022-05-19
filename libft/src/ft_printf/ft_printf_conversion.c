/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conversion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 11:29:36 by trossel           #+#    #+#             */
/*   Updated: 2022/05/19 12:51:41 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_conversion.h"

static int	get_n_digits(int n)
{
	int	c;

	if (n == 0)
		return (1);
	c = 0;
	if (n < 0)
		c++;
	while (n != 0)
	{
		n /= 10;
		c++;
	}
	return (c);
}

static int	parse_precision(const char **format)
{
	int	p;

	p = 0;
	if (ft_strchr("0123456789", *(*format + 1)))
	{
		p = ft_atoi(*format + 1);
		while (ft_strchr("0123456789", *(*format + 1)))
			(*format)++;
	}
	return (p);
}

static void	parse_flags(const char **format, t_conv_param *p)
{
	while (ft_strchr("-0# +.123456789", **format))
	{
		if (**format == '-')
			p->left_aligned = 1;
		else if (**format == '0')
			p->padding_char = '0';
		else if (**format == '#')
			p->add_prefix = 1;
		else if (**format == ' ')
			p->force_space = 1;
		else if (**format == '+')
			p->force_signed = 1;
		else if (**format == '.')
			p->precision = parse_precision(format);
		else if (ft_strchr("123456789", **format))
		{
			p->width = ft_atoi(*format);
			(*format) += get_n_digits(p->width) - 1;
		}
		(*format)++;
	}
}

static t_conv_param	get_conversion_param(const char **format)
{
	t_conv_param	p;

	p.type = 0;
	p.width = 0;
	p.precision = -1;
	p.padding_char = ' ';
	p.left_aligned = 0;
	p.force_signed = 0;
	p.force_space = 0;
	p.add_prefix = 0;
	parse_flags(format, &p);
	if (ft_strchr("cspdiuxX%", **format))
	{
		p.type = **format;
		(*format)++;
	}
	return (p);
}

int	print_conversion(const char **format, va_list val)
{
	t_conv_param	p;
	int				length;

	length = 0;
	p = get_conversion_param(format);
	if (p.type == '%' && ++length)
		ft_putchar_fd('%', 1);
	else if (p.type == 'c')
		length = print_char(va_arg(val, int), &p);
	else if (p.type == 's')
		length = print_string(va_arg(val, const char *), &p);
	else if (p.type == 'p')
		length = print_pointer(va_arg(val, void *), &p);
	else if (p.type == 'd' || p.type == 'i')
		length = print_int(va_arg(val, int), &p);
	else if (p.type == 'u')
		length = print_uint(va_arg(val, unsigned int), &p);
	else if (p.type == 'x')
		length = print_hex(va_arg(val, unsigned long), &p, 0);
	else if (p.type == 'X')
		length = print_hex(va_arg(val, unsigned long), &p, 1);
	return (length);
}
