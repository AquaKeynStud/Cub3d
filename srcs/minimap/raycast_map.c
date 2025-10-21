/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:20:43 by abouclie          #+#    #+#             */
/*   Updated: 2025/10/21 10:51:49 by abouclie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include "ui.h"
#include <math.h>

static t_dot	impact(t_data *data, t_minimap *map, t_ray *ray)
{
	t_dot	ret;

	ret.x = map->center_x + (ray->cell.x - data->player.x) * TILE_SIZE;
	ret.y = map->center_y + (ray->cell.y - data->player.y) * TILE_SIZE;
	ret.x = clamp(ret.x, 0, WIDTH_SIZE * TILE_SIZE - 1);
	ret.y = clamp(ret.y, 0, HEIGHT_SIZE * TILE_SIZE - 1);
	return (ret);
}

static void	pixel_ray(t_data *data, int steps, t_dot *inc, t_dot *pos)
{
	int	i;
	int	px;
	int	py;
	int	color;

	color = 0x00FF00;
	i = 0;
	while (i < steps)
	{
		px = (int)pos->x;
		py = (int)pos->y;
		if (px >= 0 && px < WIDTH_SIZE * TILE_SIZE && py >= 0 && py
			< HEIGHT_SIZE * TILE_SIZE)
			put_pixel(&data->dsp, (int)pos->x, (int)pos->y, color);
		else
			break ;
		pos->x += inc->x;
		pos->y += inc->y;
		i++;
	}
}

static void	draw_ray(t_data *data, t_minimap *map, t_dot *end)
{
	int		dx;
	int		dy;
	t_dot	inc;
	t_dot	pos;
	int		steps;

	dx = end->x - map->center_x;
	dy = end->y - map->center_y;
	steps = fmax(abs(dx), abs(dy));
	inc.x = dx / (double)steps;
	inc.y = dy / (double)steps;
	pos.x = map->center_x;
	pos.y = map->center_y;
	pixel_ray(data, steps, &inc, &pos);
}

void	draw_minimap_ray(t_data *data, t_minimap *map)
{
	t_ray	ray;
	t_dot	end;

	ft_memset(&ray, 0, sizeof(t_ray));
	ray.dir.x = data->player.ori.x;
	ray.dir.y = data->player.ori.y;
	init_ray(data->player, &ray);
	dda_raycasting(data->map, &ray);
	end = impact(data, map, &ray);
	draw_ray(data, map, &end);
}
