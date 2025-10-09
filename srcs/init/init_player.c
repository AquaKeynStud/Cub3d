/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:57:25 by abouclie          #+#    #+#             */
/*   Updated: 2025/10/09 14:32:05 by abouclie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"

static void	init_direction(t_data *data, float dx, float dy)
{
	data->player.dx = dx;
	data->player.dy = dy;
}

static bool	find_player(t_data *data, char c, int x, int y)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'P')
	{
		data->player.x = x + 0.5f;
		data->player.y = y + 0.5f;
		if (c == 'N')
			init_direction(data, 0.0f, -1.0f);
		else if (c == 'S')
			init_direction(data, 0.0f, 1.0f);
		else if (c == 'E')
			init_direction(data, 1.0f, 0.0f);
		else if (c == 'W')
			init_direction(data, -1.0f, 0.0f);
		return (true);
	}
	return (false);
}

void	init_player_position(t_data *data)
{
	int		y;
	int		x;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (find_player(data, data->map.map[y][x], x, y))
				return ;
			x++;
		}
		y++;
	}
}
