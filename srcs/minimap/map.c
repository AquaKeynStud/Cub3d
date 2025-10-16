/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 07:48:59 by abouclie          #+#    #+#             */
/*   Updated: 2025/10/16 10:12:31 by abouclie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub.h"

static void	draw_player_direction(t_data *data, t_minimap *map)
{
	float	length = 20.0f;
	float	step = 0.5f;
	float	t = 0;
	int		color = 0x00FF00;

	while (t < length)
	{
		int px = map->center_x + data->player.ori_x * t;
		int py = map->center_y + data->player.ori_y * t;
		mlx_pixel_put(data->mlx, data->win, px, py, color);
		t += step;
	}
}


static void	draw_square(t_data *data, t_minimap *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			mlx_pixel_put(data->mlx, data->win, map->square.start_x + x,
				map->square.start_y + y, map->square.color);
			x++;
		}
		y++;
	}
}

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
				mlx_pixel_put(data->mlx, data->win, map->center_x + x,
					map->center_y + y, 0xffa500);
			x++;
		}
		y++;
	}
}

static void	draw_line(t_data *data, t_minimap *map, int *i)
{
	int	j;
	int	map_x;
	int	map_y;

	j = 0;
	while (j < WIDTH_SIZE)
	{
		map_x = (int)(data->player.x) - WIDTH_SIZE / 2 + j;
		map_y = (int)(data->player.y) - HEIGHT_SIZE / 2 + *i;
		if (map_y >= 0 && map_y < data->map.height && map_x >= 0
			&& map_x < data->map.width)
		{
			init_square(data, map, map_x, map_y);
			draw_square(data, map);
		}
		j++;
	}
}

void	draw_map(t_data *data)
{
	t_minimap	map;
	int			i;

	map = init_map(data);
	i = 0;
	while (i < HEIGHT_SIZE)
	{
		draw_line(data, &map, &i);
		i++;
	}
	draw_player(data, &map);
	draw_player_direction(data, &map);
}
