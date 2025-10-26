/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 08:41:51 by arocca            #+#    #+#             */
/*   Updated: 2025/10/26 13:21:12 by arocca           ###   ########.fr       */
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

void	handle_door(t_door doors[DOOR_LIMIT], char **map, int y, int x)
{
	int	i;

	i = 0;
	while (i <= (DOOR_LIMIT - 1))
	{
		if (doors[i].pos.x == x && doors[i].pos.y == y)
		{
			if (doors[i].open)
			{
				doors[i].open = false;
				map[y][x] = 'D';
				printf("Porte a l'indice %ix%i, fermée\n", y, x);
			}
			else if (!doors[i].open)
			{
				doors[i].open = true;
				map[y][x] = '0';
				printf("Porte a l'indice %ix%i, ouverte\n", y, x);
			}
			return ;
		}
		i++;
	}
	return ;
}


void	check_door(t_data *data, int player_y, int player_x)
{
	int	y;
	int	x;
	int	dy;
	int	dx;

	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		y = player_y + dy;
		while (dx <= 1)
		{
			x = player_x + dx;
			if (!in_bound(x, y, data->map.width, data->map.height))
			{
				dx++;
				continue ;
			}
			handle_door(data->doors, data->map.map, y, x);
			dx++;
		}
		dy++;
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
		check_door(data, (int)floor(data->player.y), (int)floor(data->player.x));
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
