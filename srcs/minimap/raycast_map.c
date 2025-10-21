/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:20:43 by abouclie          #+#    #+#             */
/*   Updated: 2025/10/21 11:26:43 by abouclie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include "ui.h"
#include <math.h>

static t_dot	ray_to_pixel(t_data *data, t_minimap *map, t_ray *ray)
{
	t_dot end;

	end.x = map->center_x + (ray->cell.x - data->player.x) * TILE_SIZE;
	end.y = map->center_y + (ray->cell.y - data->player.y) * TILE_SIZE;
	return (end);
}

static void	draw_minimap_ray_pixel(t_data *data, t_dot *start, t_dot *end)
{
	t_dot inc = { end->x - start->x, end->y - start->y };
	int steps = fmax(fabs(inc.x), fabs(inc.y));
	t_dot pos = *start;
	int i;

	inc.x /= steps;
	inc.y /= steps;
	for (i = 0; i < steps; i++)
	{
		if ((int)pos.x < 0 || (int)pos.x >= data->dsp.width
			|| (int)pos.y < 0 || (int)pos.y >= data->dsp.height)
			break ;
		put_pixel(&data->dsp, (int)pos.x, (int)pos.y, 0x00FF00);
		pos.x += inc.x;
		pos.y += inc.y;
	}
}

void	draw_minimap_rays(t_data *data, t_minimap *map)
{
	t_ray	ray;
	t_dot	end;
	int		i;
	int		count = 60; // nombre de rayons pour le FOV
	double	angle_step = data->player.cam_fov / (count - 1);
	double	angle;

	for (i = 0; i < count; i++)
	{
		ft_memset(&ray, 0, sizeof(ray));
		angle = data->player.angle - data->player.cam_fov / 2 + i * angle_step;
		ray.dir.x = cos(angle);
		ray.dir.y = sin(angle);
		init_ray(data->player, &ray);
		dda_raycasting(data->map, &ray);
		end = ray_to_pixel(data, map, &ray);
		draw_minimap_ray_pixel(data, &(t_dot){map->center_x, map->center_y}, &end);
	}
}

static void	draw_minimap_vision_ray(t_data *data, t_minimap *map, t_dot *end)
{
	int		dx = end->x - map->center_x;
	int		dy = end->y - map->center_y;
	int		steps = fmax(abs(dx), abs(dy));
	t_dot	inc = {dx / (double)steps, dy / (double)steps};
	t_dot	pos = {map->center_x, map->center_y};
	int		i;
	int		color = 0x00FF00;

	for (i = 0; i <= steps; i++)
	{
		if ((int)pos.x >= 0 && (int)pos.x < data->dsp.width &&
			(int)pos.y >= 0 && (int)pos.y < data->dsp.height)
			put_pixel(&data->dsp, (int)pos.x, (int)pos.y, color);
		pos.x += inc.x;
		pos.y += inc.y;
	}
}

void	draw_minimap_vision(t_data *data, t_minimap *map)
{
	double	angle;
	double	start_angle = atan2(data->player.ori.y, data->player.ori.x)
						- (FOV / 2);
	double	end_angle = start_angle + FOV;
	double	step = FOV / 30; // 30 rayons suffisent sur une minimap
	t_ray	ray;
	t_dot	end;

	for (angle = start_angle; angle <= end_angle; angle += step)
	{
		ft_memset(&ray, 0, sizeof(t_ray));
		ray.dir.x = cos(angle);
		ray.dir.y = sin(angle);
		init_ray(data->player, &ray);
		dda_raycasting(data->map, &ray);

		// position d'impact sur la minimap
		end.x = map->center_x + (ray.cell.x - data->player.x) * TILE_SIZE;
		end.y = map->center_y + (ray.cell.y - data->player.y) * TILE_SIZE;

		// trace le rayon
		draw_minimap_vision_ray(data, map, &end);
	}
}
