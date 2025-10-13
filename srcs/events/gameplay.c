/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:22:45 by arocca            #+#    #+#             */
/*   Updated: 2025/10/13 18:52:32 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include <math.h>

bool	CONT = true;

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
		rotate_player(data, -ROTATION_SPEED);
	else if (data->inputs.rotate_right)
		rotate_player(data, ROTATION_SPEED);
}

void	clear_screen(t_data *data, int color)
{
	for (int y = 0; y < data->screen_height; y++)
		for (int x = 0; x < data->screen_width; x++)
			my_mlx_pixel_put(&data->screen, x, y, color);
}

int	game_loop(t_data *data)
{
	clear_screen(data, 0x0f0f0f);
	if (data->inputs.left || data->inputs.right
			|| data->inputs.forward || data->inputs.backward)
		handle_movement(data);
	if (data->inputs.rotate_left || data->inputs.rotate_right)
		handle_rotation(data);
	raycast(data);
	mlx_put_image_to_window(data->mlx, data->win, data->screen.img, 0, 0);
	return (0);
}