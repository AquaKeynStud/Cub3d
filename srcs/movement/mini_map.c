/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:55:59 by abouclie          #+#    #+#             */
/*   Updated: 2025/10/08 16:16:49 by abouclie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "config.h"

void	draw_square(t_data *data, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_pixel_put(data->mlx, data->win, x + 1, y + 1, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *data)
{
	int	i;
	int	j;
	int	tile_size;

	tile_size = 20;
	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			if (data->map.map[i][j] == '1')
				draw_square(data, j * tile_size, i * tile_size,
					tile_size, 0x0000FF);
			else
				draw_square(data, j * tile_size, i * tile_size,
					tile_size, 0xFFFFFF);
			j++;
		}
		i++;
	}
}
