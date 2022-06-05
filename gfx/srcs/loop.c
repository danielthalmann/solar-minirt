/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 22:38:32 by trossel           #+#    #+#             */
/*   Updated: 2022/06/05 22:45:33 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "mlx.h"

void	gfx_loop_hook(t_gfx_ctx *ctx, int (*funct_ptr)(), void *param)
{
	mlx_loop_hook(ctx->mlx, funct_ptr, param);
}

void	gfx_loop(t_gfx_ctx *ctx)
{
	mlx_loop(ctx->mlx);
}
