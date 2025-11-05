/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:22:45 by arocca            #+#    #+#             */
/*   Updated: 2025/11/05 09:07:42 by abouclie         ###   ########lyon.fr   */
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

void	animate_doors(t_data *data, t_image anim[5], t_door **doors)
{
	t_door	*door;
	long	tick_time;

	door = *doors;
	tick_time = get_tick_time();
	while (door && BONUS)
	{
		if (door->open && door->status < 4)
		{
			if (tick_time - door->tick > 100)
			{
				door->status += 1;
				door->tick = tick_time;
			}
			clear_background(&door->texture, &anim[door->status]);
		}
		else if (door->open && data->map.map[door->pos.y][door->pos.x] == 'D')
		{
			data->map.map[door->pos.y][door->pos.x] = '0';
			door->pos.y = -1;
			door->pos.x = -1;
			door->open = false;
		}
		door = door->next;
	}
}

void	display(t_data *data)
{
	animate_doors(data, data->assets.d_anim, &data->assets.doors);
	raycast(data);
	if (data->inputs.left_shift || data->player.stamina != MAX_STAMINA)
		display_sprint(data, data->player.sprint);
	display_crossair(data);
}

int	game_loop(t_data *data)
{
	t_image		bg;
	t_image		*dsp;
	t_inputs	input;

	bg = data->bg;
	dsp = &data->dsp;
	input = data->inputs;
	if (input.left || input.right || input.forward || input.backward)
	{
		handle_movement(data, &data->player);
		if (!data->inputs.left_shift && data->player.stamina < MAX_STAMINA)
			data->player.stamina += 1;
	}
	else if (data->player.stamina < MAX_STAMINA)
		data->player.stamina += 1;
	if (data->inputs.rotate_left)
		rotate_player(data, -ROTATION_SPEED);
	else if (data->inputs.rotate_right)
		rotate_player(data, ROTATION_SPEED);
	draw_map(data);
	clear_background(dsp, &bg);
	display(data);
	mlx_put_image_to_window(data->mlx, data->win, dsp->img, 0, 0);
	return (0);
}
