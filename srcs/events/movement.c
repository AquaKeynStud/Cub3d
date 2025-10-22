/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:17:50 by abouclie          #+#    #+#             */
/*   Updated: 2025/10/22 15:50:02 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	move_forward(t_data *data, t_player *player)
{
	float	new_x;
	float	new_y;

	new_x = player->x + player->ori.x * (PLAYER_SPEED * player->sprint_mult);
	new_y = player->y + player->ori.y * (PLAYER_SPEED * player->sprint_mult);
	if (data->map.map[(int)new_y][(int)new_x] != '1')
	{
		player->x = new_x;
		player->y = new_y;
	}
}

static void	move_backward(t_data *data, t_player *player)
{
	float	new_x;
	float	new_y;

	new_x = player->x - player->ori.x * (PLAYER_SPEED * player->sprint_mult);
	new_y = player->y - player->ori.y * (PLAYER_SPEED * player->sprint_mult);
	if (data->map.map[(int)new_y][(int)new_x] != '1')
	{
		player->x = new_x;
		player->y = new_y;
	}
}

static void	move_left(t_data *data, t_player *player)
{
	float	new_x;
	float	new_y;

	new_x = player->x + player->ori.y * (PLAYER_SPEED * player->sprint_mult);
	new_y = player->y + (-player->ori.x) * (PLAYER_SPEED * player->sprint_mult);
	if (data->map.map[(int)new_y][(int)new_x] != '1')
	{
		player->x = new_x;
		player->y = new_y;
	}
}

static void	move_right(t_data *data, t_player *player)
{
	float	new_x;
	float	new_y;

	new_x = player->x + (-player->ori.y) * (PLAYER_SPEED * player->sprint_mult);
	new_y = player->y + player->ori.x * (PLAYER_SPEED * player->sprint_mult);
	if (data->map.map[(int)new_y][(int)new_x] != '1')
	{
		player->x = new_x;
		player->y = new_y;
	}
}

void	handle_movement(t_data *data, t_player *player)
{
	if (data->inputs.left_shift && data->player.stamina <= 0)
		update_velocity(&data->inputs, &data->player, false);
	else if (data->inputs.left_shift && data->player.stamina > 0)
		data->player.stamina -= 1;
	if (data->inputs.forward)
		move_forward(data, player);
	if (data->inputs.backward)
		move_backward(data, player);
	if (data->inputs.left)
		move_left(data, player);
	if (data->inputs.right)
		move_right(data, player);
}
