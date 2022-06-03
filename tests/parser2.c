/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 14:23:18 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/22 14:23:18 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	psr_cyl_ast(char *line, int expected)
{
	t_scene	scene;
	int		ret;

	ft_fprintf(1, "TEST : [" ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET "]", line);
	scene.shapes = 0;
	ret = parse_cylinder(&scene, line);
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

/**
 * @brief 	point normal diameter height color
 * 
 * @return int 
 */
int	parser_cylinder_test(void)
{
	int	nberr;

	nberr = 0;
	ft_fprintf(1, ANSI_COLOR_MAGENTA "CYLINDER TEST\n" ANSI_COLOR_RESET);
	nberr += psr_cyl_ast("cy 50.0,0.0,20.6	0,0,1.0	 14.2 21.42 10,0,255", 0);
	nberr += psr_cyl_ast("cy 50.0,-1.0,20.6	0,1.0,1.0	42 	21.42 10,0,255", 0);
	nberr += psr_cyl_ast("cy 50.0,-1.0,20.6	0,1.0,1.0	-42 21.42 10,0,255", 1);
	nberr += psr_cyl_ast("cy 50.0,-1.0,20.6	0,1.0,1.0	42 	-21 10,0,255", 1);
	if (nberr == 0)
		ft_fprintf(1, ANSI_COLOR_GREEN "===> All OK\n" ANSI_COLOR_RESET);
	else
		ft_fprintf(1, ANSI_COLOR_RED "===> ERROR\n" ANSI_COLOR_RESET);
	return (nberr);
}

int	parser_ambient_assert(char *line, int expected)
{
	t_scene	scene;
	int		ret;

	ft_fprintf(1, "TEST : [" ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET "]", line);
	ret = parse_ambient_light(&scene, line);
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

/**
 * @brief 	point normal diameter height color
 * 
 * @return int 
 */
int	parser_ambient_test(void)
{
	int	nberr;

	nberr = 0;
	ft_fprintf(1, ANSI_COLOR_MAGENTA "AMBIENT TEST\n" ANSI_COLOR_RESET);
	nberr += parser_ambient_assert("A x	0.1	255,255,255", 1);
	nberr += parser_ambient_assert("A -0.1	255,255,255", 1);
	nberr += parser_ambient_assert("A  1	255,-255,255", 1);
	nberr += parser_ambient_assert("A  1	256,255,255", 1);
	nberr += parser_ambient_assert("A 	0.1	 255,255,255", 0);
	if (nberr == 0)
		ft_fprintf(1, ANSI_COLOR_GREEN "===> All OK\n" ANSI_COLOR_RESET);
	else
		ft_fprintf(1, ANSI_COLOR_RED "===> ERROR\n" ANSI_COLOR_RESET);
	return (nberr);
}
