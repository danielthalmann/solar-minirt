/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:06:25 by trossel           #+#    #+#             */
/*   Updated: 2022/05/19 17:03:23 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

// All line parsers
int	parse_ambiant_light(t_scene *scene, char *str);
int	parse_camera(t_scene *s, char *str);

int	parse(t_scene *scene, char *filename);
