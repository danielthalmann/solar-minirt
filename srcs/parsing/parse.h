/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:06:25 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 21:41:16 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "glmath.h"
# include "ft_printf.h"

// All line parsers
int	parse_ambient_light(t_scene *scene, char *str);
int	parse_light(t_scene *scene, char *str);
int	parse_camera(t_scene *s, char *str);
int	parse_sphere(t_scene *scene, char *str);
int	parse_plane(t_scene *scene, char *str);
int	parse_cylinder(t_scene *scene, char *str);
int	parse_cone(t_scene *scene, char *str);

// Checkers function
int	parse_check_n_elem(int diff, const char *el);
int	parse_check_non_null_vector(t_v3f *v, const char *err_msg, const char *el);
int	parse_check_positive_float(float f, const char *var, const char *el);
int	parse_check_valid_color(int color[3], const char *el);
int	parse_check_in_range(float f, float r[2], const char *var, const char *el);
int	parse_check_scene(t_scene *s);

int	parse(t_scene *scene, char *filename);

#endif
