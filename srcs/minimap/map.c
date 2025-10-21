/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 07:48:59 by abouclie          #+#    #+#             */
/*   Updated: 2025/10/21 10:57:51 by abouclie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "my_math.h"
#include "ui.h"
#include "cub.h"
#include "libft.h"

static void	draw_player(t_data *data, t_minimap *map)
{
	int	y;
	int	x;
	int	radius;

	radius = 4;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				put_pixel(&data->dsp, map->center_x + x,
					map->center_y + y, 0xffa500);
			x++;
		}
		y++;
	}
}

static void	draw_square(t_data *data, t_minimap *map)
{
	int	y;
	int	x;
	int	px;
	int	py;

	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			px = map->square.start_x + x;
			py = map->square.start_y + y;
			if (px >= 0 && px < data->dsp.width && py >= 0
				&& py < data->dsp.height)
				put_pixel(&data->dsp, px, py, map->square.color);
			x++;
		}
		y++;
	}
}

static void	set_tile(t_data *data, t_minimap *map, int i, int j)
{
	map->square.tile_x = (int)floor(data->player.x) - WIDTH_SIZE / 2 + j;
	map->square.tile_y = (int)floor(data->player.y) - HEIGHT_SIZE / 2 + i;
	map->square.start_x = map->center_x - (WIDTH_SIZE * TILE_SIZE) / 2
		+ j * TILE_SIZE - (int)round(map->frac.x * TILE_SIZE);
	map->square.start_y = map->center_y - (HEIGHT_SIZE * TILE_SIZE) / 2
		+ i * TILE_SIZE - (int)round(map->frac.y * TILE_SIZE);
	if (map->square.tile_x < 0 || map->square.tile_y < 0 || map->square.tile_x
		>= data->map.width || map->square.tile_y >= data->map.height)
		map->square.color = 0x303030;
	else if (data->map.map[map->square.tile_y][map->square.tile_x] == '1')
		map->square.color = 0xA9A9A9;
	else
		map->square.color = 0xFFFFFF;
}

static void	draw_minimap_tiles(t_data *data, t_minimap *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT_SIZE)
	{
		j = 0;
		while (j < WIDTH_SIZE)
		{
			set_tile(data, map, i, j);
			draw_square(data, map);
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *data)
{
	t_minimap	map;

	clear_image(&data->dsp, 0x000000);
	map = init_map(data);
	map.frac.x = data->player.x - floor(data->player.x);
	map.frac.y = data->player.y - floor(data->player.y);
	draw_minimap_tiles(data, &map);
	draw_player(data, &map);
	draw_minimap_ray(data, &map);
	mlx_put_image_to_window(data->mlx, data->win, data->dsp.img, 0, 0);
}
