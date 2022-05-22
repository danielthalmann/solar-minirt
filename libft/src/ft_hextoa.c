/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:25:49 by trossel           #+#    #+#             */
/*   Updated: 2021/11/16 07:38:47 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

#include <stdio.h>

static unsigned int	get_n_digits(unsigned long n)
{
	int	c;

	c = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 16;
		c++;
	}
	return (c);
}

char	*ft_hextoa(unsigned int n)
{
	int				i;
	char			*s;

	i = get_n_digits(n);
	s = malloc ((i + 1) * sizeof(char));
	if (!s)
		return (NULL);
	s[i--] = '\0';
	if (n == 0)
		s[0] = '0';
	while (n > 0)
	{
		s[i--] = "0123456789abcdef"[n % 16];
		n = n / 16;
	}
	return (s);
}

char	*ft_hextoa_l(unsigned long n)
{
	int				i;
	char			*s;

	i = get_n_digits(n);
	s = malloc ((i + 1) * sizeof(char));
	if (!s)
		return (NULL);
	s[i--] = '\0';
	if (n == 0)
		s[0] = '0';
	while (n > 0)
	{
		s[i--] = "0123456789abcdef"[n % 16];
		n = n / 16;
	}
	return (s);
}

/*
#include <stdio.h>
#include <limits.h>

void	test(int i)
{
	char	*s;

	s = ft_hextoa(i);
	printf("nb = %u\ns = '%s'\n\n", i, s);
	free(s);
}

int	main()
{
	test(0);
	test(4);
	test(42);
	test(-1);
	test(INT_MAX);
	test(INT_MIN);
	test(UINT_MAX);
}
//*/
