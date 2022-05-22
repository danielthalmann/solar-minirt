/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:57:20 by trossel           #+#    #+#             */
/*   Updated: 2021/10/13 13:28:01 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = dst;
	i = 0;
	while (i < n)
	{
		if (p + i == src)
			break ;
		p[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}
