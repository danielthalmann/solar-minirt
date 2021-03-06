/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 14:23:18 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/22 14:23:18 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	parser_test(void)
{
	int	nberr;

	nberr = 0;
	ft_fprintf(1, "PARSER TEST\n");
	nberr += parser_sphere_test();
	nberr += parser_plane_test();
	nberr += parser_cylinder_test();
	nberr += parser_ambient_test();
	if (nberr != 0)
		ft_fprintf(1, ANSI_COLOR_RED "ATTENTION ERROR\n" ANSI_COLOR_RESET);
	return (nberr);
}

int	parser_sphere_assert(char *line, int expected)
{
	t_scene	scene;
	int		ret;

	ft_fprintf(1, "TEST : [" ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET "]", line);
	scene.shapes = 0;
	ret = parse_sphere(&scene, line);
	free(scene.shapes);
	if ((expected && ret) || (!expected && !ret))
	{
		ft_fprintf(1, ANSI_COLOR_GREEN " [OK]" ANSI_COLOR_RESET "\n");
		return (0);
	}
	else
	{
		ft_fprintf(1, ANSI_COLOR_RED " [KO]" ANSI_COLOR_RESET "\n");
		return (1);
	}
}

int	parser_sphere_test(void)
{
	int	nberr;

	nberr = 0;
	ft_fprintf(1, ANSI_COLOR_MAGENTA "SPHERE TEST\n" ANSI_COLOR_RESET);
	nberr += parser_sphere_assert("sp  0,0,20  5	  255,55,0", 0);
	nberr += parser_sphere_assert("sp  0.2,0,20  5.1		255,55,0", 0);
	nberr += parser_sphere_assert("sp  0.2,0,20  5		256,55,0", 1);
	nberr += parser_sphere_assert("sp  0.2,0,20	x	5   255,55,0", 1);
	nberr += parser_sphere_assert("sp  0,0,20	-1.5   255,55,0", 1);
	nberr += parser_sphere_assert("sp  0,0,20	-1.5   255.55,0", 1);
	nberr += parser_sphere_assert("sp  0,0,20	1.5	   ,55,0", 1);
	if (nberr == 0)
		ft_fprintf(1, ANSI_COLOR_GREEN "===> All OK\n" ANSI_COLOR_RESET);
	else
		ft_fprintf(1, ANSI_COLOR_RED "===> ERROR\n" ANSI_COLOR_RESET);
	return (nberr);
}

int	parser_plane_assert(char *line, int expected)
{
	t_scene	scene;
	int		ret;

	ft_fprintf(1, "TEST : [" ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET "]", line);
	scene.shapes = 0;
	ret = parse_plane(&scene, line);
	free(scene.shapes);
	if ((expected && ret) || (!expected && !ret))
	{
		ft_fprintf(1, ANSI_COLOR_GREEN " [OK]" ANSI_COLOR_RESET "\n");
		return (0);
	}
	else
	{
		ft_fprintf(1, ANSI_COLOR_RED " [KO]" ANSI_COLOR_RESET "\n");
		return (1);
	}
}

int	parser_plane_test(void)
{
	int	nberr;

	nberr = 0;
	ft_fprintf(1, ANSI_COLOR_MAGENTA "PLANE TEST\n" ANSI_COLOR_RESET);
	nberr += parser_plane_assert("pl 0,0,0		0,1.0,0		255,0,225", 0);
	nberr += parser_plane_assert("pl -0.2,0.6,0.8  0,1.0,0		255,0,225", 0);
	nberr += parser_plane_assert("pl 0.2,0.6, 0.4  0,1.0,0		255,0,225", 0);
	nberr += parser_plane_assert("pl 0.2,0.6, 0.4  0,1.0,0		255,0,-225", 1);
	nberr += parser_plane_assert("pl 0.2,-0.6,0.4  0,1.0,0		256,55,42", 1);
	nberr += parser_plane_assert("pl 0.2,0.6,0.4	0.1.0,0		255,55,0", 1);
	nberr += parser_plane_assert("pl 0.2,0.6,0.4	0,1.0,0		-255,55,0", 1);
	if (nberr == 0)
		ft_fprintf(1, ANSI_COLOR_GREEN "===> All OK\n" ANSI_COLOR_RESET);
	else
		ft_fprintf(1, ANSI_COLOR_RED "===> ERROR\n" ANSI_COLOR_RESET);
	return (nberr);
}
