/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:01:08 by trossel           #+#    #+#             */
/*   Updated: 2022/03/07 08:50:52 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_white_space(const char c)
{
	if (c == '\n' || c == ' ' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}