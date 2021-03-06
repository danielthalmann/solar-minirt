/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:17:36 by trossel           #+#    #+#             */
/*   Updated: 2022/05/20 13:39:49 by trossel          ###   ########.fr       */
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
	else if (p->precision == -1 && p->padding_char == '0' && c < p->width)
	{
		c = p->width;
		return (c);
	}
	return (c);
}

static void	print_uint_with_prec(int fd, const char *nbr, const t_conv_param *p)
{
	int	count;

	if (p->precision == 0 && nbr[0] == '0')
		return ;
	count = ft_strlen(nbr);
	while (count < p->precision)
	{
		ft_putchar_fd('0', fd);
		count++;
	}
	while (p->padding_char == '0' && count < p->width)
	{
		ft_putchar_fd('0', fd);
		count++;
	}
	ft_putstr_fd(nbr, fd);
}

int	print_uint(int fd, unsigned int nb, t_conv_param *p)
{
	int		count;
	char	*s;

	s = ft_utoa((long)nb);
	if (!s)
		return (-1);
	if (p->precision != -1 || p->left_aligned)
		p->padding_char = ' ';
	count = get_print_width(s, p);
	if (p->left_aligned)
		print_uint_with_prec(fd, s, p);
	while (count < p->width)
	{
		ft_putchar_fd(' ', fd);
		count++;
	}
	if (!(p->left_aligned))
		print_uint_with_prec(fd, s, p);
	free(s);
	return (count);
}
