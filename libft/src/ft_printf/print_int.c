/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:30:34 by trossel           #+#    #+#             */
/*   Updated: 2022/05/20 13:37:39 by trossel          ###   ########.fr       */
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
	else if (p->precision < 0 && p->padding_char == '0' && c < p->width)
	{
		c = p->width;
		return (c);
	}
	if (nbr[0] == '-' && (c == p->precision))
		c++;
	else if (nbr[0] != '-' && (p->force_signed || p->force_space))
		c++;
	return (c);
}

static void	print_int_with_prec(int fd, int n, const char *nbr,
	const t_conv_param *p)
{
	int	count;

	if (n < 0)
		ft_putchar_fd((nbr++)[0], fd);
	else if (p->force_signed)
		ft_putchar_fd('+', fd);
	else if (p->force_space)
		ft_putchar_fd(' ', fd);
	if (p->precision == 0 && nbr[0] == '0')
		return ;
	count = ft_strlen(nbr);
	while (count < p->precision)
	{
		ft_putchar_fd('0', fd);
		count++;
	}
	if (n < 0 || p->force_signed || p->force_space)
		count++;
	while (p->padding_char == '0' && count < p->width)
	{
		ft_putchar_fd('0', fd);
		count++;
	}
	ft_putstr_fd(nbr, fd);
}

int	print_int(int fd, int nb, t_conv_param *p)
{
	int		count;
	char	*s;

	s = ft_itoa(nb);
	if (!s)
		return (-1);
	if (p->precision >= 0 || p->left_aligned)
		p->padding_char = ' ';
	count = get_print_width(s, p);
	if (p->left_aligned)
		print_int_with_prec(fd, nb, s, p);
	while (count < p->width)
	{
		ft_putchar_fd(' ', fd);
		count++;
	}
	if (!(p->left_aligned))
		print_int_with_prec(fd, nb, s, p);
	free(s);
	return (count);
}
