/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:49:43 by trossel           #+#    #+#             */
/*   Updated: 2021/11/29 07:49:21 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst2;
	t_list	*el;
	t_list	*last_el;

	if (!lst)
		return (NULL);
	lst2 = NULL;
	last_el = NULL;
	while (lst)
	{
		el = ft_lstnew(f(lst->content));
		if (!el)
			break ;
		if (last_el)
			last_el->next = el;
		if (!lst2)
			lst2 = el;
		last_el = el;
		lst = lst->next;
	}
	if (!el)
		ft_lstclear(&lst2, del);
	return (lst2);
}

/*

#include <stdio.h>

static void	*f(void *s)
{
	char	*s2;

	s2 = ft_strdup(s);
	ft_strlcpy(s2, "haha", 5);
	return (s2);
}

static void del(void *s)
{
	free(s);
}

static void print_string_list(t_list *l)
{
	t_list	*el;

	el = l;
	while (el)
	{
		printf("'%s'", (char *)el->content);
		if (el->next)
			printf(", ");
		el = el->next;
	}
}

int	main(void)
{
	t_list	*lst1;
	t_list	*lst2;

	lst1 = NULL;
	ft_lstadd_back(&lst1, ft_lstnew(ft_strdup("maew")));
	ft_lstadd_back(&lst1, ft_lstnew(ft_strdup("woof")));
	ft_lstadd_back(&lst1, ft_lstnew(ft_strdup("meuh")));
	ft_lstadd_back(&lst1, ft_lstnew(ft_strdup("booh")));
	
	lst2 = ft_lstmap(lst1, &f, &del);
	
	printf("lst1 = ");
	print_string_list(lst1);
	printf("\n");
	
	printf("lst2 = ");
	print_string_list(lst2);
	printf("\n");
}
//*/
