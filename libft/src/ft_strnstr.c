/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 09:08:11 by trossel           #+#    #+#             */
/*   Updated: 2021/10/14 14:19:28 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	s_str;
	size_t	s_nee;
	size_t	i;

	s_str = ft_strlen(str);
	s_nee = ft_strlen(to_find);
	if (s_nee == 0)
		return ((char *)str);
	i = 0;
	while (i + s_nee <= s_str && i + s_nee <= len)
	{
		if (!ft_strncmp(str + i, to_find, s_nee))
			return ((char *)(str + i));
		i++;
	}
	return (NULL);
}

/*

#include <string.h>
#include <stdio.h>

int	main(void)
{
	char	*s1;
	char	*s2;
	size_t	max;
	char	*i1;
	char	*i2;
	
	s1 = "MZIRIBMZIRIBMZE123"; 
	s2 = "MZIRIBMZE";
	max = strlen(s1);
	i1 = strnstr(s1, s1, max);
	i2 = ft_strnstr(s1, s1, max);
	
	printf("   strnstr : '%s'\n", i1);
	printf("ft_strnstr : '%s'\n", i2);
}

//*/
