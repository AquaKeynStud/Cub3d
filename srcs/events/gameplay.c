/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:22:45 by arocca            #+#    #+#             */
/*   Updated: 2025/10/17 12:36:28 by abouclie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <math.h>

static void	rotate_player(t_data *data, double angle)
{
	data->player.angle += angle;
	data->player.ori.x = cos(data->player.angle);
	data->player.ori.y = sin(data->player.angle);
	data->player.cam.y = data->player.ori.x * data->player.cam_fov;
	data->player.cam.x = -data->player.ori.y * data->player.cam_fov;
}

static void	handle_rotation(t_data *data)
{
	if (data->inputs.rotate_left)
	{
		rotate_player(data, -ROTATION_SPEED);
		data->inputs.rotate_left = 0;
	}
	if (data->inputs.rotate_right)
	{
		rotate_player(data, ROTATION_SPEED);
		data->inputs.rotate_right = 0;
	}
}

int	game_loop(t_data *data)
{
	if (data->inputs.rotate_left || data->inputs.rotate_right)
		handle_rotation(data);
	else if (data->inputs.forward || data->inputs.backward ||
		data->inputs.left || data->inputs.right)
		handle_movement(data);
	draw_map(data);
	return (0);
}