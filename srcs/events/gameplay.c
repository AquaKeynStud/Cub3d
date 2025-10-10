/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:22:45 by arocca            #+#    #+#             */
/*   Updated: 2025/10/10 15:11:10 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <math.h>

void	rotate_player(t_data *data, double angle)
{
	data->player.angle += angle;
	data->player.ori_x = cos(data->player.angle);
	data->player.ori_y = sin(data->player.angle);
}

void	handle_rotation(t_data *data)
{
	if (data->inputs.rotate_left)
		rotate_player(data, ROTATION_SPEED);
	else if (data->inputs.rotate_right)
		rotate_player(data, -ROTATION_SPEED);
}

int	game_loop(t_data *data)
{
	if (data->inputs.left || data->inputs.right
			|| data->inputs.forward || data->inputs.backward)
		handle_movement(data);
	if (data->inputs.rotate_left || data->inputs.rotate_right)
		handle_rotation(data);
	return (0);
}