/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_sscanf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:34:15 by trossel           #+#    #+#             */
/*   Updated: 2022/05/19 16:06:44 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "ft_scanf.h"

#include <stdio.h>
#include <stdlib.h>

static void	test_float(void)
{
	char		*s;
	char		*format;
	float		vals[10];

	s = "Asinglestring			+12.234  432 -12.123 0.14";
	format = "A single string %f %f %f %f";
	vals[0] = 42.40;
	vals[1] = 42.41;
	vals[2] = 42.42;
	vals[3] = 42.43;
	printf("values = (%f, %f, %f, %f)\n",
		vals[0], vals[1], vals[2], vals[3]);
	ft_sscanf(s, format, &vals[0], &vals[1], &vals[2], &vals[3]);
	printf("MY  values = (%f, %f, %f, %f)\n",
		vals[0], vals[1], vals[2], vals[3]);
	sscanf(s, format, &vals[0], &vals[1], &vals[2], &vals[3]);
	printf("HIS values = (%f, %f, %f, %f)\n",
		vals[0], vals[1], vals[2], vals[3]);
}

// static void	test_int(void)
// {
// 	char	*s;
// 	char	*format;
// 	int		vals[10];
//
// 	s = "Asinglestring			+12  432 -12 0";
// 	format = "A single string %d %d %d %d";
// 	vals[0] = 42;
// 	vals[1] = 42;
// 	vals[2] = 42;
// 	vals[3] = 42;
// 	ft_printf("values = (%d, %d, %d, %d)\n",
// 			vals[0], vals[1], vals[2], vals[3]);
// 	ft_sscanf(s, format, &vals[0], &vals[1], &vals[2], &vals[3]);
// 	ft_printf("MY  values = (%d, %d, %d, %d)\n",
// 			vals[0], vals[1], vals[2], vals[3]);
// 	sscanf(s, format, &vals[0], &vals[1], &vals[2], &vals[3]);
// 	ft_printf("HIS values = (%d, %d, %d, %d)\n",
// 			vals[0], vals[1], vals[2], vals[3]);
// }

// static void test_char(void)
// {
// 	char	*s;
// 	char	*format;
// 	char	vals[10];
// 	char	*mallocated;
//
// 	mallocated = NULL;
// 	s = "Asinglestring			d e f x";
// 	format = "A single string %c %c %c %mc";
// 	vals[0] = 'a';
// 	vals[1] = 'b';
// 	vals[2] = 'c';
// 	ft_printf("values = (%c, %c, %c), %c\n", vals[0], vals[1], vals[2], NULL);
// 	ft_sscanf(s, format, &vals[0], &vals[1], &vals[2], &mallocated);
// 	ft_printf("values = (%c, %c, %c), %c\n",
//		vals[0], vals[1], vals[2], *mallocated);
// 	free(mallocated);
// }

int	main(void)
{
	test_float();
}
