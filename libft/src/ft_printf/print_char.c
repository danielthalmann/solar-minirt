/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:30:34 by trossel           #+#    #+#             */
/*   Updated: 2022/05/20 13:34:15 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_conversion.h"
#include "libft.h"

int	print_char(int fd, char c, const t_conv_param *p)
{
	int	i;
	int	count;

	i = 1;
	count = 1;
	if (p->left_aligned)
		ft_putchar_fd(c, fd);
	while (i++ < p->width)
	{
		ft_putchar_fd(p->padding_char, fd);
		count++;
	}
	if (!(p->left_aligned))
		ft_putchar_fd(c, fd);
	return (count);
}
