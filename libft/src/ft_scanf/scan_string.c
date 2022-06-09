/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:16:56 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 08:43:59 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_scanf_conversion.h"
#include "libft.h"

#include <stdlib.h>

static int	skip_string(const char **str)
{
	while (**str && !ft_is_white_space(**str))
		(*str)++;
	return (0);
}

static	size_t	get_str_len(const char *str, size_t max_w)
{
	size_t	len;

	len = 0;
	while (*str && !ft_is_white_space(*str) && max_w > 0 && len < max_w)
	{
		len++;
		str++;
	}
	return (len);
}

static char	*init_string(char call_malloc, va_list val, int len)
{
	char	**ptr;
	char	*s;

	if (call_malloc)
	{
		ptr = va_arg(val, char **);
		if (!ptr)
			return (0);
		*ptr = malloc(1 + len);
		if (!*ptr)
			return (0);
		s = *ptr;
	}
	else
		s = va_arg(val, char *);
	return (s);
}

int	scan_string(const char **str, const t_conv_param *p, va_list val)
{
	char	*s;
	size_t	len;
	size_t	i;

	len = get_str_len(*str, p->max_width);
	i = 0;
	if (p->assign_suppression)
		return (skip_string(str));
	s = init_string(p->call_malloc, val, len);
	if (!s)
		return (0);
	while (i < len)
		*(s++) = (*str)[i++];
	s[i] = '\0';
	(*str) += len;
	return (1);
}
