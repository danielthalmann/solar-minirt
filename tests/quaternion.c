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

void	print_angle_color(float angle, const char *color)
{
	printf("%s", color);
	printf("angle (%f) \n", angle);
	printf(ANSI_COLOR_RESET "\n");
}

void	print_vect_color(t_v3f *v, const char *color)
{
	printf("%s", color);
	v3f_print(v);
	printf(ANSI_COLOR_RESET "\n");
}

int	quaternion_rotate_test(void)
{
	t_qion	qr;	
	float	i;
	t_v3f	v;
	t_v3f	v2;

	v3f_clear(&v2);
	qr.w = 0.939607;
	qr.x = -0.0;
	qr.y = -0.296257;
	qr.z = -0.05153;
	qion_normalize(&qr);
	i = 0;
	while (i >= -(2 * MATH_PI))
	{
		v2.x = 10.0 * cosf(i);
		v2.z = 10.0 * sinf(i);
		v = qion_rotation(&v2, &qr);
		printf(ANSI_COLOR_MAGENTA);
		v3f_print(&v2);
		printf(ANSI_COLOR_GREEN);
		v3f_print(&v);
		printf(ANSI_COLOR_RESET "\n");
		i -= 0.1;
	}
	return (0);
}

int	quaternion_test(void)
{
	t_qion	q;
	t_v3f	v;
	t_v3f	euler;
	float	angle;

	v3f_set(&v, 1.0, 3.0, 5.0);
	v3f_set(&euler, 0.0, M_PI, 0.0);
	print_vect_color(&v, ANSI_COLOR_BLUE);
	print_vect_color(&euler, ANSI_COLOR_YELLOW);
	q = qion_euler_rotation(euler.x, euler.y, euler.z);
	print_vect_color(&q, ANSI_COLOR_GREEN);
	v = qion_rotation(&v, &q);
	print_vect_color(&v, ANSI_COLOR_RED);
	v3f_set(&v, 5.0, 1.0, 5.0);
	print_vect_color(&v, ANSI_COLOR_BLUE);
	angle = v3f_horizontal(&v);
	print_angle_color(angle, ANSI_COLOR_RED);
	v3f_set(&v, 1.0, 5.0, 5.0);
	print_vect_color(&v, ANSI_COLOR_BLUE);
	angle = v3f_vertical(&v);
	print_angle_color(angle, ANSI_COLOR_RED);
	quaternion_rotate_test();
	return (0);
}
