/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:22:45 by arocca            #+#    #+#             */
/*   Updated: 2025/10/13 16:29:57 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include <math.h>

void	rotate_player(t_data *data, double angle)
{
	data->player.angle += angle;
	data->player.ori_x = cos(data->player.angle);
	data->player.ori_y = sin(data->player.angle);
	data->player.cam_y = data->player.ori_x * data->player.cam_fov;
	data->player.cam_x = -data->player.ori_y * data->player.cam_fov;
}

void	handle_rotation(t_data *data)
{
	if (data->inputs.rotate_left)
		rotate_player(data, ROTATION_SPEED);
	else if (data->inputs.rotate_right)
		rotate_player(data, -ROTATION_SPEED);
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

void	dda_grid(t_map map, t_ray *ray)
{
	while (!ray->hit && ray->magn < RENDER_DIST)
	{
		ray->side = (ray->magn_x < ray->magn_y);
		if (ray->side)
		{
			ray->cell_x += ray->step_x;
			ray->magn_x += ray->delta_x;
		}
		else
		{
			ray->cell_y += ray->step_y;
			ray->magn_y += ray->delta_y;
		}
		if (ray->cell_x < 0 || ray->cell_x >= map.width
				|| ray->cell_y < 0 || ray->cell_y >= map.height)
			break ;
		ray->magn = ((ray->side) * ray->magn_x) + ((!ray->side) * ray->magn_y);
		if (map.map[ray->cell_y][ray->cell_x] == '1')
			ray->hit = true;
	}
}

void	raycast(t_data *data)
{
	int		x;
	t_ray	ray;

	x = 0;
	ft_memset(&ray, 0, sizeof(t_ray));
	while (x < data->screen_width)
	{
		ray.pos = ((2 * x) / (double)data->screen_width) - 1;
		ray.dir_x = data->player.ori_x + data->player.cam_x * ray.pos;
		ray.dir_y = data->player.ori_y + data->player.cam_y * ray.pos;

		init_ray(data->player, &ray);

		dda_grid(data->map, &ray);
		
		x++;
	}
}

int	game_loop(t_data *data)
{
	if (data->inputs.left || data->inputs.right
			|| data->inputs.forward || data->inputs.backward)
		handle_movement(data);
	if (data->inputs.rotate_left || data->inputs.rotate_right)
		handle_rotation(data);

	raycast(data);
	return (0);
}