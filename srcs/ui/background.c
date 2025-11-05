/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:03:08 by arocca            #+#    #+#             */
/*   Updated: 2025/11/05 10:58:41 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "cub.h"
#include <math.h>

static int	get_bg_color(t_txts txt, float height, int center, int y)
{
	float	factor;

	factor = (float)abs(center - y);
	if (factor <= (height / BG_FADE_SPREAD) && BONUS)
		factor *= 1.0f / (height / BG_FADE_SPREAD);
	else
		factor = 1.0f;
	if (y >= center)
		return (apply_fog(txt.ceiling, factor));
	return (apply_fog(txt.floor, factor));
}

void	create_background(t_data *data, t_txts txt)
{
	int		x;
	int		y;
	int		color;
	t_idot	mapmax;

	y = 0;
	mapmax.x = WIDTH_SIZE * TILE_SIZE + MAP_PADDING - TILE_SIZE;
	mapmax.y = HEIGHT_SIZE * TILE_SIZE + MAP_PADDING - TILE_SIZE;
	while (y < data->win_h)
	{
		x = 0;
		color = get_bg_color(txt, (float)data->win_h, (data->win_h / 2.0f), y);
		while (x < data->win_w)
		{
			if (BONUS && x >= MAP_PADDING && x <= mapmax.x
				&& y >= MAP_PADDING && y <= mapmax.y)
			{
				x++;
				continue ;
			}
			data->bg.addr[y * data->bg.plen + x++] = color;
		}
		y++;
	}
}

void	display_bg_with_minimap(t_image *dst, t_image *src)
{
	int		x;
	int		y;
	t_idot	end;
	int		color;

	end.x = WIDTH_SIZE * TILE_SIZE + MAP_PADDING - TILE_SIZE;
	end.y = HEIGHT_SIZE * TILE_SIZE + MAP_PADDING - TILE_SIZE;
	if (!dst->addr || !src->addr)
		return ;
	y = 0;
	while (y < src->height)
	{
		x = 0;
		while (x < src->width)
		{
			color = src->addr[y * src->plen + x];
			if (x < MAP_PADDING || x > end.x || y < MAP_PADDING || y > end.y)
				dst->addr[y * dst->plen + x] = color;
			x++;
		}
		y++;
	}
}
