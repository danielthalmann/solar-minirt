/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conversion.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 11:24:08 by trossel           #+#    #+#             */
/*   Updated: 2021/11/16 13:00:17 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_CONVERSION_H
# define FT_PRINTF_CONVERSION_H

# include <stdarg.h>

typedef struct s_conv_param
{
	int				width;
	int				precision;
	char			type;
	char			padding_char;

	unsigned int	left_aligned : 1;
	unsigned int	force_signed : 1;
	unsigned int	force_space : 1;
	unsigned int	add_prefix : 1;
}	t_conv_param;

int	print_conversion(const char **format, va_list val);

int	print_char(char c, const t_conv_param *p);
int	print_string(const char *s, const t_conv_param *p);
int	print_int(int nb, t_conv_param *p);
int	print_uint(unsigned int nb, t_conv_param *p);
int	print_hex(unsigned int nb, t_conv_param *p, char capitalize);
int	print_pointer(void *ptr, t_conv_param *p);

#endif // !PRINTF_CONVERSION_H
