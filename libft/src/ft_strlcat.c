/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 08:01:28 by trossel           #+#    #+#             */
/*   Updated: 2021/10/18 09:35:29 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	i_d;
	unsigned int	i_s;	
	unsigned int	s_dest;
	unsigned int	s_src;

	s_dest = ft_strlen(dest);
	s_src = ft_strlen(src);
	i_d = s_dest;
	i_s = 0;
	if (s_dest >= size)
		return (size + s_src);
	while (i_s < s_src && i_d < (size - 1))
	{
		dest[i_d] = src[i_s];
		i_d++;
		i_s++;
	}
	dest[i_d] = '\0';
	return (s_dest + s_src);
}
