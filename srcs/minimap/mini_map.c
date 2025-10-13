/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:55:59 by abouclie          #+#    #+#             */
/*   Updated: 2025/10/11 16:28:05 by abouclie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "config.h"

static void	clamp_index(t_pos *pos, t_map *map)
{
	if (pos->y > map->height - 8)
		pos->y = map->height - 8;
	if (pos->y < 0)
		pos->y = 0;
	if (pos->x > map->width - 10)
		pos->x = map->width - 10;
	if (pos->x < 0)
		pos->x = 0;
}

static void	draw_line(t_data *data, t_minimap *minimap, int *i)
{
	int	j;

	j = 0;
	while (j < 10 && minimap->start.x + j < data->map.width)
	{
		if (data->map.map[minimap->start.y + *i][minimap->start.x + j] == '1')
			draw_square(data, j * minimap->tile_size, *i * minimap->tile_size,
				minimap->tile_size, 0xA9A9A9);
		else
			draw_square(data, j * minimap->tile_size, *i * minimap->tile_size,
				minimap->tile_size, 0xFFFFFF);
		j++;
	}
}

static void	handle_circle(t_data *data, t_minimap *minimap)
{
	if (data->map.height > 8 && data->map.width > 10)
		draw_circle(data, minimap->center.x, minimap->center.y, 4, 0x000000);
	else if (data->map.height <= 8 && data->map.width > 10)
		draw_circle(data, minimap->center.x,
			(int)(data->player.y * minimap->tile_size), 4, 0x000000);
	else if (data->map.height > 8 && data->map.width <= 10)
		draw_circle(data, (int)(data->player.x * minimap->tile_size),
			minimap->center.y, 4, 0x000000);
	else if (data->map.height <= 8 && data->map.width <= 10)
		draw_circle(data, (int)(data->player.x * minimap->tile_size),
			(int)(data->player.y * minimap->tile_size), 4, 0x000000);
}

void	draw_map(t_data *data)
{
	t_minimap	minimap;
	int			i;

	i = 0;
	minimap.tile_size = 20;
	minimap.center.x = 10 * minimap.tile_size / 2;
	minimap.center.y = 8 * minimap.tile_size / 2;
	minimap.start.y = data->player.y - 4;
	minimap.start.x = data->player.x - 5;
	clamp_index(&minimap.start, &data->map);
	while (minimap.start.y + i < data->map.height && i < 8)
	{
		draw_line(data, &minimap, &i);
		i++;
	}
	handle_circle(data, &minimap);
}
