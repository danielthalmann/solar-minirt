/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:23:43 by trossel           #+#    #+#             */
/*   Updated: 2021/11/10 10:46:53 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ft_printf_conversion.h"
#include "libft.h"

int	print_string(const char *s, const t_conv_param *p)
{
	int	count;
	int	n_char;

	if (!s)
		s = "(null)";
	n_char = ft_strlen(s);
	if (p->precision != -1 && p->precision < n_char)
		n_char = p->precision;
	count = n_char;
	if (p->left_aligned)
		write(1, s, n_char);
	while (count < p->width)
	{
		ft_putchar_fd(' ', 1);
		count++;
	}
	if (!p->left_aligned)
		write(1, s, n_char);
	return (count);
}
