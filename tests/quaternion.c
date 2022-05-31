/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 23:55:37 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/31 08:57:03 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	quaternionTest(void)
{
	t_qion q;
	t_v3f v;
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



	return (0);
}
