/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:08:48 by trossel           #+#    #+#             */
/*   Updated: 2021/10/14 12:42:27 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	int		v;

	i = 0;
	v = 0;
	while (i < n)
	{
		v = ((unsigned char *)(s1))[i] - ((unsigned char *)(s2))[i];
		if (v)
			break ;
		i++;
	}
	return (v);
}
