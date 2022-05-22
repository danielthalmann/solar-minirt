/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 09:58:29 by trossel           #+#    #+#             */
/*   Updated: 2022/04/04 09:54:40 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		l;

	if (!s1 || !s2)
		return (NULL);
	l = ft_strlen(s1) + ft_strlen(s2) + 1;
	s = malloc(l * sizeof(char));
	if (!s)
		return (NULL);
	ft_strlcpy(s, s1, l);
	ft_strlcat(s, s2, l);
	return (s);
}

char	*ft_strjoin_3(char const *s1, char const *s2, char const *s3)
{
	char	*s;
	int		l;
	int		i;

	if (!s1 || !s2 || !s3)
		return (NULL);
	l = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	s = malloc(l * sizeof(char));
	if (!s)
		return (NULL);
	s[l - 1] = '\0';
	i = 0;
	while (*s1)
		s[i++] = *(s1++);
	while (*s2)
		s[i++] = *(s2++);
	while (*s3)
		s[i++] = *(s3++);
	return (s);
}

/*

#include <stdio.h>

#define N_STR 4

int	main()
{
	char * array[] = {
    "First entry",
    "Second entry",
	"",
    "Fourth entry",
	};
	char *sep = "@@@";

	char	*join = ft_strjoin(N_STR, array, sep);

	if(join == NULL)
	{
		printf("Join cannot get its own memory :(\n");
		return (2);
	}
	if (join[0] == '\0')
	{
		printf("Error : join is empty\n");
		free(join);
		return(1);
	}
	for(int i = 0; i < N_STR; i++)
	{
		printf("strs[%d] = \"%s\"\n", i, array[i]);
	}
	printf("sep = '%s'\njoin = \"%s\"\n", sep, join);
	int l = ft_strlen(join);
	printf("last char (l=%d)  = '%c'\n", l, join[l] + '0');
	//printf("not last char = '%c'\n", join[35]);
	free(join);
}
//*/
