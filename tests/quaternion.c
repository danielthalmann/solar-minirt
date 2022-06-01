/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 23:55:37 by dthalman          #+#    #+#             */
/*   Updated: 2022/06/01 19:31:07 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	quaternionTest(void)
{
	t_qion q;
	t_v3f v;
	t_v3f v2;
	t_v3f euler;
	float angle;
	//t_v3f conj;

	v.x = 1.0;
	v.y = 3.0;
	v.z = 5.0;

	euler.x = 0.0;
	euler.y = M_PI;
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

	v = qion_rotation(&v, &q);

	printf(ANSI_COLOR_RED);
	v3f_print(&v);
	printf(ANSI_COLOR_RESET "\n");

	v.x = 5.0;
	v.y = 1.0;
	v.z = 5.0;
	printf(ANSI_COLOR_BLUE);
	v3f_print(&v);
	printf(ANSI_COLOR_RESET "\n");

	angle = v3f_horizontal(&v);
	printf(ANSI_COLOR_RED);
	printf(" %f \n", angle);
	printf(ANSI_COLOR_RESET "\n");
	

	v.x = 1.0;
	v.y = 5.0;
	v.z = 5.0;
	printf(ANSI_COLOR_BLUE);
	v3f_print(&v);
	printf(ANSI_COLOR_RESET "\n");

	angle = v3f_vertical(&v);
	printf(ANSI_COLOR_RED);
	printf(" %f \n", angle);
	printf(ANSI_COLOR_RESET "\n");

	v3f_clear(&v2);

	t_qion qr ;	
	qr.w = 0.939607;
	qr.x = -0.163449;
	qr.y = -0.296257;
	qr.z = -0.05153;

	qr.w = 0.939607;
	qr.x = -0.0;
	qr.y = -0.296257;
	qr.z = -0.05153;

	qion_normalize(&qr);
		
	for (float i = 0; i >= -(2 * MATH_PI); i-=0.1)
	{
		v2.x = 10.0 * cosf(i);
		v2.z = 10.0 * sinf(i);

		v = qion_rotation(&v2, &qr);
		
		printf(ANSI_COLOR_MAGENTA);
		v3f_print(&v2);
		printf(ANSI_COLOR_GREEN);
		v3f_print(&v);
		printf(ANSI_COLOR_RESET "\n");	
	}
/*
	for (float i = 0; i < M_PI; i+=0.1)
	{
		t_qion qr = qion_euler_rotation(0, i, 0);	
		v = qion_rotation(&v2, &qr);
		
		printf(ANSI_COLOR_GREEN);
		v3f_print(&v);
		printf(ANSI_COLOR_RESET "\n");	
	}
*/
	return (0);
}
