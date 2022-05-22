/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 09:59:56 by trossel           #+#    #+#             */
/*   Updated: 2022/04/06 10:25:53 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

/* Return a copy of a string, without the part between start and start + n.
 * */
char	*ft_strcut(const char *str, size_t start, int n)
{
	size_t	i;
	size_t	length;
	size_t	input_length;
	char	*str2;

	if (!str)
		return (NULL);
	input_length = ft_strlen(str);
	if (n <= 0 || start > input_length)
		return (ft_strdup(str));
	if ((size_t)n > input_length - start)
		n = input_length - start;
	length = ft_strlen(str) - n;
	str2 = malloc ((length + 1) * sizeof(char));
	str2[length] = '\0';
	i = 0;
	while (i < start)
		str2[i++] = *(str++);
	str += n;
	while (i < length)
		str2[i++] = *(str++);
	return (str2);
}

/*
int	main(int ac, char *av[])
{
	char *str = "abcdefghijklmnopqrstuvwxyz";
	int	start = 15;
	int	n = 10;
	char *str2;

	if (ac == 4)
	{
		str = av[1];
		start = ft_atoi(av[2]);
		n = ft_atoi(av[3]);
	}
	str2 = ft_strcut(str, start, n);
	ft_printf("start = %d\nn = %d\ns  = '%s'\ns2 = '%s'\n",
		start, n, str, str2);
	free(str2);
	return (0);
}

//*/
