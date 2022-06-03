/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:03:04 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/20 10:11:57 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include <stdlib.h>
# include <stdio.h>
# include <assert.h>
# include "glmath.h"
# include "error.h"
# include "error.h"
# include "libft.h"
# include "colors.h"
# include "../srcs/parsing/parse.h"

int	plane_test(void);

int	parser_test(void);
int	parser_sphere_assert(char *line, int expected);
int	parser_sphere_test(void);
int	parser_plane_assert(char *line, int expected);
int	parser_plane_test(void);
int	psr_cyl_ast(char *line, int expected);
int	parser_cylinder_test(void);
int	parser_ambient_assert(char *line, int expected);
int	parser_ambient_test(void);

int	quaternion_test(void);

#endif
