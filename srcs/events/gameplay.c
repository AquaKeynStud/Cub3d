/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:22:45 by arocca            #+#    #+#             */
/*   Updated: 2025/10/15 10:33:45 by abouclie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	game_loop(t_data *data)
{
	if (data->inputs.rotate_left || data->inputs.rotate_right)
		handle_rotation(data);
	else if (data->inputs.forward || data->inputs.backward ||
		data->inputs.left || data->inputs.right)
		handle_movement(data);
	draw_map(data);
	return (0);
}