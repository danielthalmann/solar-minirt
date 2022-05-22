/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 11:27:26 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/22 11:27:26 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
# include "ft_printf.h"

int	notEnoughArguments()
{
	ft_fprintf(STDERR_FILENO, "Error\n");
	ft_fprintf(STDERR_FILENO, "not enough arguments\n");
	return (1);
}
