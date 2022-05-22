/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 11:10:29 by trossel           #+#    #+#             */
/*   Updated: 2021/10/18 10:52:10 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	get_number_of_substrings(const char *str, char c)
{
	int	is_in_word;
	int	n;

	is_in_word = 0;
	n = 0;
	while (*str != '\0')
	{
		if (*str == c)
		{
			is_in_word = 0;
			str++;
			continue ;
		}
		if (!is_in_word)
		{
			is_in_word = 1;
			n++;
		}
		str++;
	}
	return (n);
}

static void	free_tab(char **strs, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static void	populate(char **strs, const char *str, char c, int n)
{
	int	i;
	int	l;

	i = 0;
	while (i < n)
	{
		l = 0;
		while (*str == c)
			str++;
		while (*(str + l) && *(str + l) != c)
			l++;
		strs[i] = ft_substr(str, 0, l);
		if (!strs[i])
		{
			free_tab(strs, i - 1);
			return ;
		}
		str += l;
		i++;
	}
}

char	**ft_split(const char *str, char c)
{
	int			n;
	char		**strs;

	if (!str)
		return (NULL);
	n = get_number_of_substrings(str, c);
	strs = malloc((n + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	strs[n] = NULL;
	populate(strs, str, c, n);
	return (strs);
}

/*
#include <stdio.h>

int	main(void)
{
	char	*s;
	char	**ss;
	int		i;

	s = "      split       this for   me  !       ";
	s = ft_strdup("Tripouille");
	printf("s = '%s'\n", s);
	ss = ft_split(s, ' ');
	if (!ss)
	{
		printf("SS is NULL.\n");
		return (0);
	}
	i = 0;
	while (ss[i])
	{
		printf("ss[%d] = '%s'\n", i, ss[i]);
		i++;
	}
	free(s);
}
//*/
