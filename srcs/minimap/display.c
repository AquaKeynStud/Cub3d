/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:40:43 by abouclie          #+#    #+#             */
/*   Updated: 2025/10/11 15:40:55 by abouclie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_square(t_data *data, int px, int py, int size, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			mlx_pixel_put(data->mlx, data->win, px + x, py + y, color);
			x++;
		}
		y++;
	}
}

void	draw_circle(t_data *data, int cx, int cy, int radius, int color)
{
	int	y;
	int	x;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				mlx_pixel_put(data->mlx, data->win, cx + x, cy + y, color);
			x++;
		}
		y++;
	}
}