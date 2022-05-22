/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 14:33:26 by trossel           #+#    #+#             */
/*   Updated: 2022/03/15 14:09:22 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_white_space(const char *c)
{
	if (*c == '\n' || *c == '\t' || *c == '\r'
		|| *c == '\v' || *c == '\f' || *c == ' ')
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	long	n;
	long	sign;

	n = 0;
	sign = 1;
	while (is_white_space(str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		n *= 10;
		n += (*str - '0');
		str++;
	}
	return (sign * n);
}

/*
#include <stdio.h>
#include <stdlib.h>

static void test(char *s)
{
	int		i1;
	int		i2;

	i1 = ft_atoi(s);
	i2 = atoi(s);
	if (i1 == i2)
		printf("OK ! (%d)\n", i1);
	else
		printf("expected: %d\nGot     : %d\n", i2, i1);
}

int main(void)
{
	test("  \v\t+++-+-+-+231786465239847dskljfghlekjagh");
	test("  \v\t\r\f\n+231786465239847dskljfghlekjagh");
	test("-2147483648");
	test("2147483648");
	test("2147483647");
	test("0");
	test("42a");
	test("+42");
	test("-42");
	test("--42");
	test("+-42");
}

//*/
