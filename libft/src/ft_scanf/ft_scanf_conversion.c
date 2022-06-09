/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scanf_conversion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 11:29:36 by trossel           #+#    #+#             */
/*   Updated: 2022/06/08 19:21:05 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_scanf_conversion.h"
#include "ft_printf.h"

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

static void	parse_flags(const char **format, t_conv_param *p)
{
	while (ft_strchr("*'m0123456789", **format))
	{
		if (**format == '*')
			p->assign_suppression = 1;
		else if (**format == '\'')
			p->thousand_sep = 1;
		else if (**format == 'm')
			p->call_malloc = 1;
		else if (ft_strchr("0123456789", **format))
		{
			p->max_width = ft_atoi(*format);
			(*format) += get_n_digits(p->max_width) - 1;
		}
		(*format)++;
	}
}

static t_conv_param	get_conversion_param(const char **format)
{
	t_conv_param	p;

	p.type = 0;
	p.max_width = -1;
	p.assign_suppression = 0;
	p.thousand_sep = 0;
	p.call_malloc = 0;
	parse_flags(format, &p);
	if (ft_strchr("cspdifuxX%", **format))
	{
		p.type = **format;
		(*format)++;
	}
	return (p);
}

int	ft_sscanf_conversion(const char **str, const char **format, va_list val)
{
	t_conv_param	p;
	int				err;

	err = 0;
	p = get_conversion_param(format);
	if (p.type == '%' && ++err)
		ft_putchar_fd('%', 1);
	else if (p.type == 'c')
		err = scan_char(str, &p, val);
	else if (p.type == 'd' || p.type == 'i')
		err = scan_int(str, &p, val);
	else if (p.type == 'f')
		err = scan_float(str, &p, val);
	else if (p.type == 's')
		err = scan_string(str, &p, val);
	return (err);
}
