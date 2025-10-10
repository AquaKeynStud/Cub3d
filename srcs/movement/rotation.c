/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 01:46:36 by abouclie          #+#    #+#             */
/*   Updated: 2025/10/10 14:27:53 by abouclie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <math.h>

void	rotate_player(t_data *data, double angle)
{
	double	old_ori_x;
	double	old_ori_y;

	old_ori_x = data->player.ori_x;
	old_ori_y = data->player.ori_y;
	data->player.ori_x = cos(angle) * old_ori_x - sin(angle) * old_ori_y;
	data->player.ori_x = sin(angle) * old_ori_x + cos(angle) * old_ori_y;
}

void	handle_rotation(t_data *data)
{
	if (data->inputs.rotate_left)
		rotate_player(data, ROTATION_SPEED);
	else if (data->inputs.rotate_right)
		rotate_player(data, -ROTATION_SPEED);
}
