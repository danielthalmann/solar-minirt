/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_atof.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:31:51 by trossel           #+#    #+#             */
/*   Updated: 2022/05/19 16:06:09 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft.h"
#include "ft_printf.h"

int	main(void)
{
	char	*s;
	float	f;

	s = "    -23.346644239847923874";
	f = ft_atof(s);
	ft_printf("As %%f is not implemented in ft_printf, modify the test to use "
		"the real printf. Thank you !\n");
	(void)f;
	return (0);
}

// Add the following to the main:
/*
	printf("MY : s = '%s'\n\tf = %f\n", s, f);
	f = atof(s);
	printf("HIS: s = '%s'\n\tf = %f\n", s, f);
//*/
