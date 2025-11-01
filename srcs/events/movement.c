/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:17:50 by abouclie          #+#    #+#             */
/*   Updated: 2025/11/01 09:13:37 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"

static void	move_forward(t_data *data, t_player *player)
{
	float	x;
	float	y;

	x = player->x + player->ori.x * (PLAYER_SPEED * player->sprint_mult);
	y = player->y + player->ori.y * (PLAYER_SPEED * player->sprint_mult);
	if (!in_str(data->map.map[(int)y][(int)x], "1D", false))
	{
		player->x = x;
		player->y = y;
	}
	else if (data->map.map[(int)y][(int)x] == 'D' && is_door_open(data->assets.doors, y, x))
	{
		player->y = y;
		player->x = x;
	}
}

static void	move_backward(t_data *data, t_player *player)
{
	float	x;
	float	y;

	x = player->x - player->ori.x * (PLAYER_SPEED * player->sprint_mult);
	y = player->y - player->ori.y * (PLAYER_SPEED * player->sprint_mult);
	if (!in_str(data->map.map[(int)y][(int)x], "1D", false))
	{
		player->x = x;
		player->y = y;
	}
	else if (data->map.map[(int)y][(int)x] == 'D' && is_door_open(data->assets.doors, y, x))
	{
		player->y = y;
		player->x = x;
	}
}

static void	move_left(t_data *data, t_player *player)
{
	float	x;
	float	y;

	x = player->x + player->ori.y * (PLAYER_SPEED * player->sprint_mult);
	y = player->y + (-player->ori.x) * (PLAYER_SPEED * player->sprint_mult);
	if (!in_str(data->map.map[(int)y][(int)x], "1D", false))
	{
		player->x = x;
		player->y = y;
	}
	else if (data->map.map[(int)y][(int)x] == 'D' && is_door_open(data->assets.doors, y, x))
	{
		player->y = y;
		player->x = x;
	}
}

static void	move_right(t_data *data, t_player *player)
{
	float	x;
	float	y;

	x = player->x + (-player->ori.y) * (PLAYER_SPEED * player->sprint_mult);
	y = player->y + player->ori.x * (PLAYER_SPEED * player->sprint_mult);
	if (!in_str(data->map.map[(int)y][(int)x], "1D", false))
	{
		player->x = x;
		player->y = y;
	}
	else if (data->map.map[(int)y][(int)x] == 'D' && is_door_open(data->assets.doors, y, x))
	{
		player->y = y;
		player->x = x;
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
