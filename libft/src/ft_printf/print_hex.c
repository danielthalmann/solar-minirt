/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:42:04 by trossel           #+#    #+#             */
/*   Updated: 2021/11/16 12:59:56 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_printf_conversion.h"
#include "libft.h"

static void	ft_toupper_str(char *s)
{
	while (*s)
	{
		*s = ft_toupper(*s);
		s++;
	}
}

static int	get_print_width(const char *nbr, const t_conv_param *p)
{
	int	c;

	c = ft_strlen(nbr);
	if (p->precision == 0 && nbr[0] == '0')
		c = 0;
	if (p->precision > c)
		c = p->precision;
	if (p->add_prefix && nbr[0] != '0')
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

static void	print_hex_with_prec(const char *nbr, const t_conv_param *p, char c)
{
	int	count;

	if (p->precision == 0 && nbr[0] == '0')
		return ;
	count = ft_strlen(nbr);
	if (p->add_prefix && nbr[0] != '0' && c)
		ft_putstr_fd("0X", 1);
	else if (p->add_prefix && nbr[0] != '0')
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

int	print_hex(unsigned int nb, t_conv_param *p, char capitalize)
{
	int		count;
	char	*s;

	s = ft_hextoa(nb);
	if (!s)
		return (-1);
	if (capitalize)
		ft_toupper_str(s);
	if (p->precision != -1 || p->left_aligned)
		p->padding_char = ' ';
	count = get_print_width(s, p);
	if (p->left_aligned)
		print_hex_with_prec(s, p, capitalize);
	while (count < p->width)
	{
		ft_putchar_fd(' ', 1);
		count++;
	}
	if (!(p->left_aligned))
		print_hex_with_prec(s, p, capitalize);
	free(s);
	return (count);
}
