/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:25:49 by trossel           #+#    #+#             */
/*   Updated: 2021/11/15 20:27:08 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

#include <stdio.h>

static unsigned int	get_n_digits(long nb)
{
	int	c;

	c = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb *= -1;
		c++;
	}
	while (nb > 0)
	{
		nb /= 10;
		c++;
	}
	return (c);
}

char	*ft_utoa(unsigned int n)
{
	int				i;
	char			*s;
	long			nb;

	nb = n;
	i = get_n_digits(nb);
	s = malloc ((i + 1) * sizeof(char));
	if (!s)
		return (NULL);
	s[i--] = '\0';
	if (n == 0)
		s[0] = '0';
	while (nb > 0)
	{
		s[i--] = '0' + nb % 10;
		nb = nb / 10;
	}
	return (s);
}

/*
#include <stdio.h>
#include <limits.h>

void	test(unsigned int i)
{
	char	*s;

	s = ft_utoa(i);
	printf("nb = %d\ns = '%s'\n\n", i, s);
	free(s);
}

int	main()
{
	test(0);
	test(4);
	test(42);
	test(-42);
	test(INT_MAX);
	test(INT_MIN);
}
//*/
