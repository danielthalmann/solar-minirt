/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:47:30 by trossel           #+#    #+#             */
/*   Updated: 2021/10/13 14:35:06 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = dst;
	if (!dst && !src)
		return (dst);
	if (dst <= src)
	{
		i = 0;
		while (i < n)
		{
			p[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i)
		{
			p[i - 1] = ((unsigned char *)src)[i - 1];
			i--;
		}
	}
	return (dst);
}
