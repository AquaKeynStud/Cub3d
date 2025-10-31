/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:22:45 by arocca            #+#    #+#             */
/*   Updated: 2025/10/31 10:31:40 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "cub.h"
#include "libft.h"
#include <math.h>

void	rotate_player(t_data *data, double angle)
{
	data->player.angle += angle;
	data->player.ori.x = cos(data->player.angle);
	data->player.ori.y = sin(data->player.angle);
	data->player.cam.y = data->player.ori.x * data->player.cam_fov;
	data->player.cam.x = -data->player.ori.y * data->player.cam_fov;
}

int	mouse_move(int x, int y, t_data *data)
{
	int	delta_x;

	(void)y;
	if (!data->inputs.allow_mouse || x == data->win_w / 2)
		return (0);
	delta_x = x - data->inputs.mouse_x;
	data->inputs.mouse_x = x;
	rotate_player(data, delta_x * SENSIBILITY);
	mlx_mouse_move(data->mlx, data->win, data->win_w / 2, data->win_h / 2);
	data->inputs.mouse_x = data->win_w / 2;
	return (0);
}

void	handle_rotation(t_data *data)
{
	if (data->inputs.rotate_left)
		rotate_player(data, -ROTATION_SPEED);
	else if (data->inputs.rotate_right)
		rotate_player(data, ROTATION_SPEED);
}

void	copy_non_black_pixels(t_image *dst, t_image *src)
{
	int	x;
	int	y;
	int	color;

	if (!dst->addr || !src->addr)
		return;

	for (y = 0; y < src->height; y++)
	{
		for (x = 0; x < src->width; x++)
		{
			color = src->addr[y * src->plen + x];
			if (color != 0x000000)
				dst->addr[y * dst->plen + x] = color;
		}
	}
}


void	handle_door_animation(t_data *data, t_door doors[DOOR_LIMIT])
{
	int	i;

	i = 0;
	while (i <= DOOR_LIMIT - 1)
	{
		if (doors[i].open && doors[i].status < 5)
		{
			doors[i].frames += 1;
			if (doors[i].frames >= 10)
			{
				doors[i].frames = 0;
				doors[i].status += 1;
				if (doors[i].status >= 5)
					data->map.map[doors[i].pos.y][doors[i].pos.x] = '0';
				else
					copy_non_black_pixels(&data->assets.door, &data->assets.d_anim[doors[i].status - 1]);
			}
		}
		i++;
	}
}

int	game_loop(t_data *data)
{
	t_image		bg;
	t_image		*dsp;
	t_inputs	input;

	bg = data->bg;
	dsp = &data->dsp;
	input = data->inputs;
	if (input.left || input.right || input.forward || input.backward)
	{
		handle_movement(data, &data->player);
		if (!data->inputs.left_shift && data->player.stamina < MAX_STAMINA)
			data->player.stamina += 1;
	}
	else if (data->player.stamina < MAX_STAMINA)
		data->player.stamina += 1;
	if (input.rotate_left || input.rotate_right)
		handle_rotation(data);
	ft_memcpy(dsp->addr, bg.addr, data->win_w * data->win_h * sizeof(int));

	handle_door_animation(data, data->doors);

	raycast(data);
	if (data->inputs.left_shift || data->player.stamina != MAX_STAMINA)
		display_sprint(data, data->player.sprint);
	display_crossair(data);
	mlx_put_image_to_window(data->mlx, data->win, dsp->img, 0, 0);
	return (0);
}
