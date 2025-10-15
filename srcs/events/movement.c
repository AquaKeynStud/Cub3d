/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:17:50 by abouclie          #+#    #+#             */
/*   Updated: 2025/10/15 14:33:54 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	move_forward(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->player.x + data->player.ori.x * PLAYER_SPEED;
	new_y = data->player.y + data->player.ori.y * PLAYER_SPEED;
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

	new_x = data->player.x - data->player.ori.x * PLAYER_SPEED;
	new_y = data->player.y - data->player.ori.y * PLAYER_SPEED;
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

	new_x = data->player.x + data->player.ori.y * PLAYER_SPEED;
	new_y = data->player.y + (-data->player.ori.x) * PLAYER_SPEED;
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

	new_x = data->player.x + (-data->player.ori.y) * PLAYER_SPEED;
	new_y = data->player.y + data->player.ori.x * PLAYER_SPEED;
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
