/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:17:50 by abouclie          #+#    #+#             */
/*   Updated: 2025/10/08 16:16:59 by abouclie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	move_forward(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->player.x + data->player.dx * data->player.speed;
	new_y = data->player.y + data->player.dy * data->player.speed;
	if (data->map.map[(int)new_y][(int)new_x] != '1')
	{
		data->player.dx = new_x;
		data->player.dy = new_y;
	}
}

void	move_back(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->player.x - data->player.dx * data->player.speed;
	new_y = data->player.y - data->player.dy * data->player.speed;
	if (data->map.map[(int)new_y][(int)new_x] != '1')
	{
		data->player.dx = new_x;
		data->player.dy = new_y;
	}
}

void	move_right(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->player.x + data->player.dy * data->player.speed;
	new_y = data->player.y + (-data->player.dx) * data->player.speed;
	if (data->map.map[(int)new_y][(int)new_x] != '1')
	{
		data->player.dx = new_x;
		data->player.dy = new_y;
	}
}

void	move_left(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->player.x + (-data->player.dy) * data->player.speed;
	new_y = data->player.y + data->player.dx * data->player.speed;
	if (data->map.map[(int)new_y][(int)new_x] != '1')
	{
		data->player.dx = new_x;
		data->player.dy = new_y;
	}
}