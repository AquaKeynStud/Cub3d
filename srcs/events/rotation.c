/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 01:46:36 by abouclie          #+#    #+#             */
/*   Updated: 2025/10/16 11:27:12 by abouclie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <math.h>

void	normalize_vector(double *x, double *y)
{
	double length;
	
	length = sqrt((*x) * (*x) + (*y) * (*y));
	if (length != 0)
	{
		*x /= length;
		*y /= length;
	}
}

void	rotate_player(t_data *data, double angle)
{
	double	old_ori_x;
	double	old_ori_y;

	old_ori_x = data->player.ori_x;
	old_ori_y = data->player.ori_y;
	data->player.ori_x = cos(angle) * old_ori_x - sin(angle) * old_ori_y;
	data->player.ori_y = sin(angle) * old_ori_x + cos(angle) * old_ori_y;
	normalize_vector(&data->player.ori_x, &data->player.ori_y);
}

void	handle_rotation(t_data *data)
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
