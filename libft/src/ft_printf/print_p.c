/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:42:04 by trossel           #+#    #+#             */
/*   Updated: 2021/11/16 13:07:11 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_printf_conversion.h"
#include "libft.h"

static int	get_print_width(const char *nbr, const t_conv_param *p)
{
	int	c;

	c = ft_strlen(nbr);
	if (p->precision == 0 && nbr[0] == '0')
		c = 0;
	if (p->precision > c)
		c = p->precision;
	if (p->add_prefix)
		c += 2;
	if (p->precision == -1 && p->padding_char == '0' && c < p->width)
	{
		c = p->width;
		return (c);
	}
	if (nbr[0] == '-' && (c == p->precision || c == p->width))
		c++;
	return (c);
}

static void	print_ptr_with_prec(const char *nbr, const t_conv_param *p)
{
	int	count;

	if (p->precision == 0 && nbr[0] == '0')
		return ;
	count = ft_strlen(nbr);
	if (p->add_prefix)
		ft_putstr_fd("0x", 1);
	while (count < p->precision)
	{
		ft_putchar_fd('0', 1);
		count++;
	}
	if (p->add_prefix && nbr[0] != '0')
		count += 2;
	while (p->padding_char == '0' && count < p->width)
	{
		ft_putchar_fd('0', 1);
		count++;
	}
	ft_putstr_fd(nbr, 1);
}

int	print_pointer(void *ptr, t_conv_param *p)
{
	int		count;
	char	*s;

	p->add_prefix = 1;
	s = ft_hextoa_l((unsigned long)ptr);
	if (!s)
		return (-1);
	if (p->precision != -1 || p->left_aligned)
		p->padding_char = ' ';
	count = get_print_width(s, p);
	if (p->left_aligned)
		print_ptr_with_prec(s, p);
	while (count < p->width)
	{
		ft_putchar_fd(' ', 1);
		count++;
	}
	if (!(p->left_aligned))
		print_ptr_with_prec(s, p);
	free(s);
	return (count);
}
