/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:17:50 by abouclie          #+#    #+#             */
/*   Updated: 2025/10/10 14:29:21 by abouclie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	move_forward(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->player.x + data->player.ori_x * data->player.speed;
	new_y = data->player.y + data->player.ori_y * data->player.speed;
	if (data->map.map[(int)new_y][(int)new_x] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

static void	move_backward(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->player.x - data->player.ori_x * data->player.speed;
	new_y = data->player.y - data->player.ori_y * data->player.speed;
	if (data->map.map[(int)new_y][(int)new_x] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

static void	move_right(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->player.x + data->player.ori_y * data->player.speed;
	new_y = data->player.y + (-data->player.ori_x) * data->player.speed;
	if (data->map.map[(int)new_y][(int)new_x] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

static void	move_left(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->player.x + (-data->player.ori_y) * data->player.speed;
	new_y = data->player.y + data->player.ori_x * data->player.speed;
	if (data->map.map[(int)new_y][(int)new_x] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	handle_movement(t_data *data)
{
	if (data->inputs.forward)
		move_forward(data);
	else if (data->inputs.backward)
		move_backward(data);
	else if (data->inputs.left)
		move_left(data);
	else if (data->inputs.right)
		move_right(data);
}