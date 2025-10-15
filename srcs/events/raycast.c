/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:59:14 by arocca            #+#    #+#             */
/*   Updated: 2025/10/15 17:52:42 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "cub.h"
#include <math.h>
#include "libft.h"

void	init_ray(t_player player, t_ray *ray)
{
	ray->cell.x = (int)player.x;
	ray->cell.y = (int)player.y;
	ray->delta.x = fabs(1 / ray->dir.x);
	ray->delta.y = fabs(1 / ray->dir.y);
	ray->step.x = (ray->dir.x > 0) - (ray->dir.x < 0);
	ray->step.y = (ray->dir.y > 0) - (ray->dir.y < 0);
	if (ray->dir.x < 0)
		ray->magn.x = (player.x - ray->cell.x) * ray->delta.x;
	else
		ray->magn.x = ((ray->cell.x + 1) - player.x) * ray->delta.x;
	if (ray->dir.y < 0)
		ray->magn.y = (player.y - ray->cell.y) * ray->delta.y;
	else
		ray->magn.y = ((ray->cell.y + 1) - player.y) * ray->delta.y;
}

static void	get_ray_result(t_data *data, t_ray *ray)
{
	if (!ray->side)
	{
		ray->magnitude = ray->magn.x - ray->delta.x;
		ray->pos = data->player.y + ray->magnitude * ray->dir.y;
	}
	else
	{
		ray->magnitude = ray->magn.y - ray->delta.y;
		ray->pos = data->player.x + ray->magnitude * ray->dir.x;
	}
	ray->pos -= floor(ray->pos);
}

static void	dda_raycasting(t_map map, t_ray *ray)
{
	while (!ray->hit)
	{
		ray->side = (ray->magn.x >= ray->magn.y);
		if (!ray->side)
		{
			ray->magn.x += ray->delta.x;
			ray->cell.x += ray->step.x;
		}
		else
		{
			ray->magn.y += ray->delta.y;
			ray->cell.y += ray->step.y;
		}
		if (!in_bound(ray->cell.x, ray->cell.y, map.width, map.height))
			break ;
		if (map.map[(int)ray->cell.y][(int)ray->cell.x] == '1')
			ray->hit = true;
	}
}

void	raycast(t_data *data)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < data->win_w)
	{
		ft_memset(&ray, 0, sizeof(t_ray));
		ray.origin = 2 * x / ((double)data->win_w) - 1;
		ray.dir.x = data->player.ori.x + data->player.cam.x * ray.origin;
		ray.dir.y = data->player.ori.y + data->player.cam.y * ray.origin;
		init_ray(data->player, &ray);
		dda_raycasting(data->map, &ray);
		if (ray.hit)
			get_ray_result(data, &ray);
		display_wall(data, ray, x);
		x++;
	}
}
