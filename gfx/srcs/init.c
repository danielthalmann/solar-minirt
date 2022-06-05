/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:44:17 by trossel           #+#    #+#             */
/*   Updated: 2022/06/06 07:32:52 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "mlx.h"

#include <stdlib.h>

t_gfx_ctx	*gfx_init(void)
{
	t_gfx_ctx	*ctx;

	ctx = malloc(sizeof(*ctx));
	if (!ctx)
		return (NULL);
	ctx->_ctx = mlx_init();
	if (!ctx->_ctx)
	{
		free(ctx);
		return (NULL);
	}
	return (ctx);
}
