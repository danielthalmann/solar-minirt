/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scanf_conversion.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 11:24:08 by trossel           #+#    #+#             */
/*   Updated: 2022/06/08 18:46:54 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SCANF_CONVERSION_H
# define FT_SCANF_CONVERSION_H

# include <stdarg.h>

typedef struct s_conv_param
{
	int				max_width;
	char			type;

	unsigned int	assign_suppression;
	unsigned int	thousand_sep;
	unsigned int	call_malloc;
}	t_conv_param;

int	ft_sscanf_conversion(const char **str, const char **format, va_list val);

int	scan_char(const char **str, const t_conv_param *p, va_list val);
int	scan_int(const char **str, const t_conv_param *p, va_list val);
int	scan_float(const char **str, const t_conv_param *p, va_list val);
int	scan_string(const char **str, const t_conv_param *p, va_list val);

#endif // !PRINTF_CONVERSION_H
