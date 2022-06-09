/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 11:27:26 by dthalman          #+#    #+#             */
/*   Updated: 2022/06/09 09:19:59 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

int	not_enough_arguments(void)
{
	ft_fprintf(STDERR_FILENO, "Error\n");
	ft_fprintf(STDERR_FILENO, "not enough arguments\n");
	return (1);
}
