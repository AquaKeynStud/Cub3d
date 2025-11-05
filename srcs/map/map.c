/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 07:48:59 by abouclie          #+#    #+#             */
/*   Updated: 2025/11/05 11:25:22 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "my_math.h"
#include "ui.h"
#include "cub.h"
#include "libft.h"

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
				data->dsp.addr[py * data->dsp.plen + px] = map->square.color;
			x++;
		}
		y++;
	}
}

static void	set_tile(t_data *data, t_minimap *map, int i, int j)
{
	map->square.tile_x = (int)floor(data->player.x) - WIDTH_SIZE / 2 + j;
	map->square.tile_y = (int)floor(data->player.y) - HEIGHT_SIZE / 2 + i;
	map->square.start_x = map->center_x + (map->square.tile_x
			- data->player.x) * TILE_SIZE;
	map->square.start_y = map->center_y + (map->square.tile_y
			- data->player.y) * TILE_SIZE;
	if (map->square.tile_x < 0 || map->square.tile_y < 0
		|| map->square.tile_x >= data->map.width
		|| map->square.tile_y >= data->map.height)
		map->square.color = BG_COLOR;
	else if (data->map.map[map->square.tile_y][map->square.tile_x] == '1')
		map->square.color = WALL_COLOR;
	else if (data->map.map[map->square.tile_y][map->square.tile_x] == 'D')
		map->square.color = DOOR_COLOR;
	else
		map->square.color = FLOOR_COLOR;
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

	map = init_map(data);
	map.frac.x = data->player.x - floor(data->player.x);
	map.frac.y = data->player.y - floor(data->player.y);
	draw_minimap_tiles(data, &map);
	draw_player_triangle(data, &map, 8);
	mlx_put_image_to_window(data->mlx, data->win, data->dsp.img, 0, 0);
}
