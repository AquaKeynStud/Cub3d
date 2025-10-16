/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:35:29 by abouclie          #+#    #+#             */
/*   Updated: 2025/10/16 10:16:02 by abouclie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <math.h>

void	init_square(t_data *data, t_minimap *map, int x, int y)
{
	t_square	square;
	double		offset_x;
	double		offset_y;

	offset_x = (x - data->player.x) * TILE_SIZE;
	offset_y = (y - data->player.y) * TILE_SIZE;
	square.start_x = map->center_x + offset_x;
	square.start_y = map->center_y + offset_y;
	if (data->map.map[y][x] == '1')
		square.color = 0xA9A9A9;
	else
		square.color = 0xFFFFFF;
	map->square = square;
}

t_minimap	init_map(t_data *data)
{
	t_minimap	map;

	map.center_x = WIDTH_SIZE * TILE_SIZE / 2;
	map.center_y = HEIGHT_SIZE * TILE_SIZE / 2;
	init_square(data, &map, (int)floor(data->player.x),
		(int)floor(data->player.y));
	return (map);
}
