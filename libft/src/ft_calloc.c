/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 09:07:19 by trossel           #+#    #+#             */
/*   Updated: 2021/10/12 09:35:14 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	size_t			l;
	unsigned char	*bptr;

	l = nmemb * size;
	ptr = malloc(l);
	if (!ptr)
		return (ptr);
	bptr = ptr;
	while (l--)
	{
		*(bptr++) = 0;
	}
	return (ptr);
}
