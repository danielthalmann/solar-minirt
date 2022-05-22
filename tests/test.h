/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:03:04 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/20 10:11:57 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>
# include <stdio.h>
# include <assert.h>
# include "glmath.h"
# include "error.h"
# include "error.h"
# include "libft.h"
# include "colors.h"
# include "parsing/parse.h"

int	planeTest(void);
int	parserTest(void);
int	parserSphereAssert(char *line, int expected);
int	parserSphereTest(void);
int	parserPlaneAssert(char *line, int expected);
int	parserPlaneTest(void);
int	parserCylinderAssert(char *line, int expected);
int	parserCylinderTest(void);
int	parserAmbientAssert(char *line, int expected);
int	parserAmbientTest(void);
int	parserTest(void);

#endif
