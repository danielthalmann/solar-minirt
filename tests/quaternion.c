/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 23:55:37 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/30 23:55:37 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	quaternionTest(void)
{
	t_qion q;
	t_v3f v;
	t_v3f euler;
	//t_v3f conj;


	v.x = 1.0;
	v.y = 3.0;
	v.z = 5.0;

	euler.x = 0.0;
	euler.y = M_PI_4;
	euler.z = 0.0;

	printf(ANSI_COLOR_BLUE);
	v3f_print(&v);
	printf(ANSI_COLOR_RESET "\n");

	printf(ANSI_COLOR_YELLOW);
	v3f_print(&euler);
	printf(ANSI_COLOR_RESET "\n");

	q = qion_euler_rotation(euler.x, euler.y, euler.z);

	printf(ANSI_COLOR_GREEN);
	v3f_print(&q);
	printf(ANSI_COLOR_RESET "\n");

	
//	v.w = 1 - v.w;

//	conj = qion_create(&q);
//	conj.x *= -1;
//	conj.y *= -1;
//	conj.z *= -1;
//
//	v = qion_product(&q, &v);
//	v = qion_product(&v, &conj);

	v = qion_rotation(&v, &q);

	printf(ANSI_COLOR_RED);
	v3f_print(&v);
	printf(ANSI_COLOR_RESET "\n");

	
	return (0);
}
