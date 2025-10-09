/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:55:59 by abouclie          #+#    #+#             */
/*   Updated: 2025/10/09 14:35:39 by abouclie         ###   ########lyon.fr   */
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
			if (x*x + y*y <= radius*radius)
				mlx_pixel_put(data->mlx, data->win, cx + x, cy + y, color);
			x++;
		}
		y++;
	}
}

void	draw_map(t_data *data)
{
	int	i;
	int	j;
	int	tile_size;

	tile_size = 20;
	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			if (data->map.map[i][j] == '1')
				draw_square(data, j * tile_size, i * tile_size,
					tile_size, 0xA9A9A9);
			else if (data->map.map[i][j] == '0')
				draw_square(data, j * tile_size, i * tile_size,
					tile_size, 0xFFFFFF);
			else
			{
				draw_square(data, j * tile_size, i * tile_size,
					tile_size, 0xFFFFFF);
				draw_circle(data, (int)(data->player.x * tile_size),
					(int)(data->player.y * tile_size),
							4, 0x000000);
			}
			j++;
		}
		i++;
	}
}
