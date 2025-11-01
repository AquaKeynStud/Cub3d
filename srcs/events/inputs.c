/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 08:41:51 by arocca            #+#    #+#             */
/*   Updated: 2025/11/01 10:19:59 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <math.h>
#include "ft_printf.h"

int	end_loop(t_data *data)
{
	mlx_loop_end(data->mlx);
	return (0);
}

void	handle_mouse(t_data *data, t_inputs *inputs)
{
	if (inputs->allow_mouse)
	{
		inputs->allow_mouse = false;
		info("Mouse is now disabled", INFO, NULL);
		mlx_mouse_show(data->mlx, data->win);
	}
	else
	{
		inputs->allow_mouse = true;
		info("Mouse is now enabled", INFO, NULL);
		inputs->mouse_x = data->win_w / 2;
		mlx_mouse_hide(data->mlx, data->win);
	}
	return ;
}

void	update_velocity(t_inputs *inputs, t_player *player, bool active)
{
	if (active)
	{
		player->sprint_mult = 2;
		inputs->left_shift = true;
	}
	else
	{
		player->sprint_mult = 1;
		inputs->left_shift = false;
	}
	return ;
}

void	check_door(t_data *data, t_door **doors)
{
	int		dir_y;
	int		dir_x;
	t_door	*door;

	dir_y = (int)(data->player.y + data->player.ori.y * 1.0);
	dir_x = (int)(data->player.x + data->player.ori.x * 1.0);
	if (!in_bound(dir_x, dir_y, data->map.width, data->map.height))
		return ;
	else if (data->map.map[dir_y][dir_x] == 'D')
	{
		door = get_door(*doors, dir_y, dir_x);
		if (door && !door->open)
			door->open = true;
	}
}

int	key_pressed(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		mlx_loop_end(data->mlx);
	else if (keycode == KEY_A)
		data->inputs.left = true;
	else if (keycode == KEY_D)
		data->inputs.right = true;
	else if (keycode == KEY_W)
		data->inputs.forward = true;
	else if (keycode == KEY_S)
		data->inputs.backward = true;
	else if (keycode == KEY_E)
		check_door(data, &data->assets.doors);
	else if (keycode == KEY_LALT)
		handle_mouse(data, &data->inputs);
	else if (keycode == KEY_LEFT)
		data->inputs.rotate_left = true;
	else if (keycode == KEY_RIGHT)
		data->inputs.rotate_right = true;
	else if (keycode == KEY_LSHIFT)
		update_velocity(&data->inputs, &data->player, true);
	else if (keycode >= 'a' && keycode <= 'z')
		ft_printf(NO_KEY_ERR, MAPLOG, keycode - 32, EOL);
	return (0);
}

int	key_released(int keycode, t_data *data)
{
	if (keycode == KEY_A)
		data->inputs.left = false;
	else if (keycode == KEY_D)
		data->inputs.right = false;
	else if (keycode == KEY_W)
		data->inputs.forward = false;
	else if (keycode == KEY_S)
		data->inputs.backward = false;
	else if (keycode == KEY_LEFT)
		data->inputs.rotate_left = false;
	else if (keycode == KEY_RIGHT)
		data->inputs.rotate_right = false;
	else if (keycode == KEY_LSHIFT)
		update_velocity(&data->inputs, &data->player, false);
	return (0);
}
