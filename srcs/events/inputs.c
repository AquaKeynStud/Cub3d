/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 08:41:51 by arocca            #+#    #+#             */
/*   Updated: 2025/10/11 02:20:47 by abouclie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"

int	close_on_esc(int keycode, t_data *data)
{
	if (keycode == 65307)
		mlx_loop_end(data->mlx);
	return (0);
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
	else if (keycode == KEY_LEFT)
		data->inputs.rotate_left = true;
	else if (keycode == KEY_RIGHT)
		data->inputs.rotate_right = true;
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
	return (0);
}
