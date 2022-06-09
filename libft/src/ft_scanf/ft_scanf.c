/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scanf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 08:02:16 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 08:52:08 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#include "ft_scanf_conversion.h"
#include "libft.h"
#include "ft_printf.h"

static int	ft_vsscanf(const char *str, const char *format, va_list args)
{
	int	n_conv;

	n_conv = 0;
	while (*str && *format)
	{
		if (ft_is_white_space(*format))
		{
			while (ft_is_white_space(*str))
					str++;
			format++;
		}
		else if (*format != '%')
		{
			if (*(str++) != *(format++))
				break ;
		}
		else
		{
			format++;
			if (!ft_sscanf_conversion(&str, &format, args))
				break ;
			n_conv++;
		}
	}
	return (n_conv);
}

int	ft_sscanf(const char *str, const char *format, ...)
{
	int		n;
	va_list	args;

	va_start(args, format);
	n = ft_vsscanf(str, format, args);
	va_end(args);
	return (n);
}

/*

#include <stdlib.h>
#include <stdio.h>

int	main (void)
{
	char	*s = "Thisisastring verylong verycool";
	int		n_elem;

	printf("-------------------------------\n");

	// STRING TESTS
	char	*ss[10];
	for (int i = 0; i < 5; i++)
		ss[i] = calloc(1, 30);
	for (int i = 5; i < 10; i++)
		ss[i] = NULL;
	n_elem =    sscanf(s, "%s %s %s", ss[0], ss[1], ss[2]);
	n_elem = ft_sscanf(s, "%6s %6s %s", ss[0], ss[1], ss[2]);
	n_elem =    sscanf(s, "%6s %6s %s", ss[0], ss[1], ss[2]);
	n_elem = ft_sscanf(s, "%6ms", &ss[6]);
	n_elem =    sscanf(s, "%6ms", &ss[7]);
	printf("n_elem = %d\n", n_elem);
	for (int i = 0; i < 10; i++)
	{
		if (ss[i] && ss[i][0])
			printf("ss[%d] = %s\n", i, ss[i]);
		if (ss[i])
			free(ss[i]);
	}
	
	// CHAR TESTS
	char	c;
	char	*ptr = NULL;
	n_elem = ft_sscanf(s, "%c", &c);
	n_elem = ft_sscanf(&s[3], "%mc", &ptr);
	// n_elem =    sscanf(s, "%c", &c);
	// n_elem =    sscanf(&s[3], "%mc", &ptr);

	printf("n_elem = %d\n", n_elem);
	printf("c = '%c'\n", c);
	printf("*ptr = '%c'\n", *ptr);
	free(ptr);
}
//*/
