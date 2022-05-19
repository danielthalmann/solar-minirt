/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 14:19:53 by trossel           #+#    #+#             */
/*   Updated: 2022/03/30 16:47:17 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	idx;
	int				val;

	idx = 0;
	val = 0;
	while (!val && (s2[idx] != '\0' || s1[idx] != '\0'))
	{
		val = (unsigned char)s1[idx] - (unsigned char)s2[idx];
		idx++;
	}
	return (val);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	idx;
	int				val;

	idx = 0;
	val = 0;
	while (!val && idx < n && (s2[idx] != '\0' || s1[idx] != '\0'))
	{
		val = (unsigned char)s1[idx] - (unsigned char)s2[idx];
		idx++;
	}
	return (val);
}
