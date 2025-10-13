/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:59:14 by arocca            #+#    #+#             */
/*   Updated: 2025/10/13 19:55:07 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <math.h>
#include "libft.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->slen + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

static void	get_wall(t_data *data, t_ray ray, int x)
{
	int	end;
	int	start;
	int	color;
	int	line_len;

	line_len = (int)(data->screen_height / ray.dist);
	end = line_len / 2 + data->screen_height / 2;
	start = -line_len / 2 + data->screen_height / 2;
	if (ray.side)
		color = 0x0000FF;
	else
		color = 0x000088;
	if (start < 0)
		start = 0;
	if (end >= data->screen_height)
		end = data->screen_height - 1;
	for (int y = start; y <= end; y++)
		my_mlx_pixel_put(&data->screen, x, y, color);
}

void	init_ray(t_player player, t_ray *ray)
{
	ray->delta_x = fabs(1 / ray->dir_x);
	ray->delta_y = fabs(1 / ray->dir_y);
	ray->cell_x = (int)player.x;
	ray->cell_y = (int)player.y;
	ray->step_x = (ray->dir_x > 0) - (ray->dir_x < 0);
	ray->step_y = (ray->dir_y > 0) - (ray->dir_y < 0);
	if (ray->dir_x < 0)
		ray->magn_x = (player.x - ray->cell_x) * ray->delta_x;
	else
		ray->magn_x = ((ray->cell_x + 1) - player.x) * ray->delta_x;
	if (ray->dir_y < 0)
		ray->magn_y = (player.y - ray->cell_y) * ray->delta_y;
	else
		ray->magn_y = ((ray->cell_y + 1) - player.y) * ray->delta_y;
}

static void	dda_grid(t_map map, t_ray *ray)
{
	while (!ray->hit)
	{
		if (ray->magn_x < ray->magn_y)
		{
			ray->magn_x += ray->delta_x;
			ray->cell_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->magn_y += ray->delta_y;
			ray->cell_y += ray->step_y;
			ray->side = 1;
		}
		if (!in_bound(ray->cell_x, ray->cell_y, map.width, map.height))
			break ;
		ray->magn = ((ray->side) * ray->magn_x) + ((!ray->side) * ray->magn_y);
		if (map.map[ray->cell_y][ray->cell_x] == '1')
		{
			ray->hit = true;
			if (ray->side == 0)
				ray->dist = ray->magn_x - ray->delta_x;
			else
				ray->dist = ray->magn_y - ray->delta_y;
		}
	}
}

void	raycast(t_data *data)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < data->screen_width)
	{
		ft_memset(&ray, 0, sizeof(t_ray));
		ray.pos = 2 * x / ((double)data->screen_width) - 1;
		ray.dir_x = data->player.ori_x + data->player.cam_x * ray.pos;
		ray.dir_y = data->player.ori_y + data->player.cam_y * ray.pos;
		init_ray(data->player, &ray);
		dda_grid(data->map, &ray);
		get_wall(data, ray, x);
		x++;
	}
}
