/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 18:44:53 by trossel           #+#    #+#             */
/*   Updated: 2021/10/13 15:50:49 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static unsigned int	ft_pow10(int exp)
{
	int				i;
	unsigned int	res;

	if (exp > 9)
		return (0);
	i = 0;
	res = 1;
	while (i < exp)
	{
		res *= 10;
		i++;
	}
	return (res);
}

static unsigned int	get_highest_pow_exp(unsigned int n)
{
	int	pow_exp;

	pow_exp = 9;
	while (pow_exp > 0 && n / ft_pow10(pow_exp) == 0)
	{
		pow_exp--;
	}
	return (pow_exp);
}

void	ft_putnbr_fd(int nb, int fd)
{
	char			s;
	unsigned int	n;
	unsigned int	i;
	int				h;

	if (nb < 0)
	{
		write(fd, "-", 1);
		n = -((unsigned int)(nb));
	}
	else
		n = ((unsigned int)(nb));
	h = get_highest_pow_exp(n);
	while (h >= 0)
	{	
		i = n / ft_pow10(h);
		s = '0' + i;
		write(fd, &s, 1);
		n = n % ft_pow10(h);
		h--;
	}
}
