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

int	parserTest(void)
{
	int	nberr;

	nberr = 0;
	ft_fprintf(1, "PARSER TEST\n");
	nberr += parserSphereTest();
	nberr += parserPlaneTest();
	nberr += parserCylinderTest();
	nberr += parserAmbientTest();
	if (nberr != 0)
		ft_fprintf(1, ANSI_COLOR_RED "ATTENTION ERROR\n" ANSI_COLOR_RESET);
	return (nberr);
}

int	parserSphereAssert(char *line, int expected)
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

int	parserSphereTest(void)
{
	int	nberr;

	nberr = 0;
	ft_fprintf(1, ANSI_COLOR_MAGENTA "SPHERE TEST\n" ANSI_COLOR_RESET);
	nberr += parserSphereAssert("sp  0,0,20  5	  255,55,0", 0);
	nberr += parserSphereAssert("sp  0.2,0,20  5.1		255,55,0", 0);
	nberr += parserSphereAssert("sp  0.2,0,20  5		256,55,0", 1);
	nberr += parserSphereAssert("sp  0.2,0,20	x	5   255,55,0", 1);
	nberr += parserSphereAssert("sp  0,0,20	-1.5   255,55,0", 1);
	nberr += parserSphereAssert("sp  0,0,20	-1.5   255.55,0", 1);
	nberr += parserSphereAssert("sp  0,0,20	1.5	   ,55,0", 1);
	if (nberr == 0)
		ft_fprintf(1, ANSI_COLOR_GREEN "===> All OK\n" ANSI_COLOR_RESET);
	else
		ft_fprintf(1, ANSI_COLOR_RED "===> ERROR\n" ANSI_COLOR_RESET);
	return (nberr);
}

int	parserPlaneAssert(char *line, int expected)
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

int	parserPlaneTest(void)
{
	int	nberr;

	nberr = 0;
	ft_fprintf(1, ANSI_COLOR_MAGENTA "PLANE TEST\n" ANSI_COLOR_RESET);
	nberr += parserPlaneAssert("pl 	0,0,0		0,1.0,0		255,0,225", 0);
	nberr += parserPlaneAssert("pl 	-0.2,0.6,0.8  0,1.0,0		255,0,225", 0);
	nberr += parserPlaneAssert("pl 	0.2,0.6, 0.4  0,1.0,0		255,0,225", 0);
	nberr += parserPlaneAssert("pl 	0.2,0.6, 0.4  0,1.0,0		255,0,-225", 1);
	nberr += parserPlaneAssert("pl  0.2,-0.6,0.4  0,1.0,0		256,55,42", 1);
	nberr += parserPlaneAssert("pl  0.2,0.6,0.4		0.1.0,0		255,55,0", 1);
	nberr += parserPlaneAssert("pl  0.2,0.6,0.4		0,1.0,0		-255,55,0", 1);
	if (nberr == 0)
		ft_fprintf(1, ANSI_COLOR_GREEN "===> All OK\n" ANSI_COLOR_RESET);
	else
		ft_fprintf(1, ANSI_COLOR_RED "===> ERROR\n" ANSI_COLOR_RESET);
	return (nberr);
}

int	parserCylinderAssert(char *line, int expected)
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
int	parserCylinderTest(void)
{
	int	nberr;

	nberr = 0;
	ft_fprintf(1, ANSI_COLOR_MAGENTA "CYLINDER TEST\n" ANSI_COLOR_RESET);
	nberr += parserCylinderAssert("cy 50.0,0.0,20.6	0,0,1.0		14.2 	21.42 10,0,255", 0);
	nberr += parserCylinderAssert("cy 50.0,-1.0,20.6	0,1.0,1.0	42 	21.42 10,0,255", 0);
	nberr += parserCylinderAssert("cy 50.0,-1.0,20.6	0,1.0,1.0	-42 	21.42 10,0,255", 1);
	nberr += parserCylinderAssert("cy 50.0,-1.0,20.6	0,1.0,1.0	42 	-21 10,0,255", 1);
	if (nberr == 0)
		ft_fprintf(1, ANSI_COLOR_GREEN "===> All OK\n" ANSI_COLOR_RESET);
	else
		ft_fprintf(1, ANSI_COLOR_RED "===> ERROR\n" ANSI_COLOR_RESET);
	return (nberr);
}


int	parserAmbientAssert(char *line, int expected)
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
int	parserAmbientTest(void)
{
	int	nberr;

	nberr = 0;
	ft_fprintf(1, ANSI_COLOR_MAGENTA "AMBIENT TEST\n" ANSI_COLOR_RESET);
	nberr += parserAmbientAssert("A x	0.1	255,255,255", 1);
	nberr += parserAmbientAssert("A -0.1	255,255,255", 1);
	nberr += parserAmbientAssert("A  1	255,-255,255", 1);
	nberr += parserAmbientAssert("A  1	256,255,255", 1);
	nberr += parserAmbientAssert("A 	0.1	 255,255,255", 0);
	if (nberr == 0)
		ft_fprintf(1, ANSI_COLOR_GREEN "===> All OK\n" ANSI_COLOR_RESET);
	else
		ft_fprintf(1, ANSI_COLOR_RED "===> ERROR\n" ANSI_COLOR_RESET);
	return (nberr);
}
