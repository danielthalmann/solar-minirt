/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:32:59 by trossel           #+#    #+#             */
/*   Updated: 2022/04/06 18:40:01 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*el;
	t_list	*el2;

	if (!lst)
		return ;
	el = *lst;
	while (el)
	{
		del(el->content);
		el2 = el;
		el = el->next;
		free(el2);
	}
	*lst = NULL;
}

/*

#include <stdio.h>

static void print_string_list(t_list *l)
{
	t_list	*el;

	el = l;
	while (el)
	{
		printf("'%s'", el->content);
		if (el->next)
			ft_printf(", ");
		el = el->next;
	}
}

static void	del(void *data)
{
	free(data);
}

int main(void)
{
	t_list	*lst1;

	lst1 = NULL;
	ft_lstadd_back(&lst1, ft_lstnew(ft_strdup("maew")));
	ft_lstadd_back(&lst1, ft_lstnew(ft_strdup("woof")));
	ft_lstadd_back(&lst1, ft_lstnew(ft_strdup("meuh")));
	ft_lstadd_back(&lst1, ft_lstnew(ft_strdup("booh")));

	ft_printf("lst1 = ");
	print_string_list(lst1);
	ft_printf("\n");

	ft_lstclear(&lst1->next->next, &del);

	ft_printf("lst1 = ");
	print_string_list(lst1);
	ft_printf("\n");

}
//*/
