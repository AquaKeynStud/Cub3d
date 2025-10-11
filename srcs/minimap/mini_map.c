/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:55:59 by abouclie          #+#    #+#             */
/*   Updated: 2025/10/11 14:40:39 by abouclie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "config.h"

void	draw_square(t_data *data, int px, int py, int size, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			mlx_pixel_put(data->mlx, data->win, px + x, py + y, color);
			x++;
		}
		y++;
	}
}

void	draw_circle(t_data *data, int cx, int cy, int radius, int color)
{
	int	y;
	int	x;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				mlx_pixel_put(data->mlx, data->win, cx + x, cy + y, color);
			x++;
		}
		y++;
	}
}

static void	clamp_index(int *index, int max, int size)
{
	if (*index > max - size)
		*index = max - size;
	if (*index < 0)
		*index = 0;
}

void	draw_map(t_data *data)
{
	t_minimap	minimap;
	int			i;
	int			j;

	i = 0;
	minimap.tile_size = 20;
	minimap.center.x = 10 * minimap.tile_size / 2;
	minimap.center.y = 8 * minimap.tile_size / 2;
	minimap.start.y = data->player.y - 4;
	clamp_index(&minimap.start.y, data->map.height, 8);
	minimap.start.x = data->player.x - 5;
	clamp_index(&minimap.start.x, data->map.width, 10);
	while (i < data->map.height && i < 8)
	{
		j = 0;
		while (j < data->map.width && j < 10)
		{
			if (data->map.map[minimap.start.y][minimap.start.x] == '1')
				draw_square(data, j * minimap.tile_size, i * minimap.tile_size,
					minimap.tile_size, 0xA9A9A9);
			else if (data->map.map[minimap.start.y][minimap.start.x] == '0')
				draw_square(data, j * minimap.tile_size, i * minimap.tile_size,
					minimap.tile_size, 0xFFFFFF);
			else
			{
				draw_square(data, j * minimap.tile_size, i * minimap.tile_size,
					minimap.tile_size, 0xFFFFFF);
			}
			j++;
			minimap.start.x++;
		}
		i++;
		minimap.start.y++;
	}
	draw_circle(data, minimap.center.x, minimap.center.y, 4, 0x000000);
}
