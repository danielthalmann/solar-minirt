/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 10:26:15 by trossel           #+#    #+#             */
/*   Updated: 2022/03/30 18:09:32 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;

	if (!s1)
		return (NULL);
	if (!set)
		set = " \t\n\r\f\v";
	start = 0;
	end = ft_strlen(s1);
	if (ft_strlen(set) == 0 || end == 0)
		return (ft_strdup(s1));
	while (start <= end && ft_strchr(set, s1[start]))
		start++;
	while (end && ft_strchr(set, s1[end - 1]))
		end--;
	if (end == 0)
		start = end;
	return (ft_substr(s1, start, end - start));
}
