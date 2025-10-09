/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 08:41:51 by arocca            #+#    #+#             */
/*   Updated: 2025/10/09 20:35:52 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "ft_printf.h"

int	key_pressed(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		mlx_loop_end(data->mlx);
	else if (keycode == KEY_W)
		data->inputs.forward = true;
	else if (keycode == KEY_S)
		data->inputs.backward = true;
	else if (keycode == KEY_A)
		data->inputs.rotate_left = true;
	else if (keycode == KEY_D)
		data->inputs.rotate_right = true;
	else if (keycode >= 'a' && keycode <= 'z')
		ft_printf("%s🈲 The key : %c isn't handled 🈲%s", MAPLOG, keycode - 32, EOL);
	return (0);
}

int	key_released(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->inputs.forward = false;
	else if (keycode == KEY_S)
		data->inputs.backward = false;
	else if (keycode == KEY_A)
		data->inputs.rotate_left = false;
	else if (keycode == KEY_D)
		data->inputs.rotate_right = false;
	return (0);
}
