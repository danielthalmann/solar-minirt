/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:30:34 by trossel           #+#    #+#             */
/*   Updated: 2021/11/15 10:42:42 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_conversion.h"
#include "libft.h"

int	print_char(char c, const t_conv_param *p)
{
	int	i;
	int	count;

	i = 1;
	count = 1;
	if (p->left_aligned)
		ft_putchar_fd(c, 1);
	while (i++ < p->width)
	{
		ft_putchar_fd(p->padding_char, 1);
		count++;
	}
	if (!(p->left_aligned))
		ft_putchar_fd(c, 1);
	return (count);
}
