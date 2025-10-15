/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:22:45 by arocca            #+#    #+#             */
/*   Updated: 2025/10/15 18:46:28 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "cub.h"
#include "libft.h"
#include <math.h>

void	rotate_player(t_data *data, double angle)
{
	data->player.angle += angle;
	data->player.ori.x = cos(data->player.angle);
	data->player.ori.y = sin(data->player.angle);
	data->player.cam.y = data->player.ori.x * data->player.cam_fov;
	data->player.cam.x = -data->player.ori.y * data->player.cam_fov;
}

int	mouse_move(int x, int y, t_data *data)
{
	int	delta_x;

	(void)y;
	if (!data->inputs.allow_mouse || x == data->win_w / 2)
		return (0);
	delta_x = x - data->inputs.mouse_x;
	data->inputs.mouse_x = x;
	rotate_player(data, delta_x * SENSIBILITY);
	mlx_mouse_move(data->mlx, data->win, data->win_w / 2, data->win_h / 2);
	data->inputs.mouse_x = data->win_w / 2;
	return (0);
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
	int	x;
	int	y;

	y = 0;
	while (y < data->win_h)
	{
		x = 0;
		while (x < data->win_w)
			put_pixel(&data->screen, x++, y, color);
		y++;
	}
}

int	game_loop(t_data *data)
{
	clear_screen(data, 0x0f0f0f);
	if (data->inputs.left || data->inputs.right
		|| data->inputs.forward || data->inputs.backward)
		handle_movement(data);
	if (data->inputs.rotate_left || data->inputs.rotate_right)
		handle_rotation(data);
	display_background(data);
	raycast(data);
	mlx_put_image_to_window(data->mlx, data->win, data->screen.img, 0, 0);
	return (0);
}
