/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 10:02:25 by trossel           #+#    #+#             */
/*   Updated: 2021/10/13 14:25:05 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	unsigned int	idx;
	unsigned int	src_size;

	src_size = 0;
	while (src[src_size] != '\0')
		src_size++;
	if (dstsize == 0)
		return (src_size);
	idx = 0;
	while (src[idx] != '\0' && idx < dstsize - 1)
	{
		dest[idx] = src[idx];
		idx++;
	}
	if (dstsize != 0)
		dest[idx] = '\0';
	return (src_size);
}
