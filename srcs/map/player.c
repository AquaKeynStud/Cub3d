/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:00:42 by abouclie          #+#    #+#             */
/*   Updated: 2025/11/05 09:40:29 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include "ui.h"
#include <math.h>

static void	draw_scanline(t_data *data, int y, double x_min, double x_max)
{
	int	x;

	x = (int)x_min;
	while (x <= (int)x_max)
	{
		if (x >= 0 && x < data->dsp.width && y >= 0 && y < data->dsp.height)
			data->dsp.addr[y * data->dsp.plen + x] = PLR_COLOR;
		x++;
	}
}

static void	draw_triangle_line(t_data *data, t_dot *pts, int y)
{
	double	x_min;
	double	x_max;
	double	b[2];
	t_dot	a[2];
	int		i;

	i = 0;
	x_min = 1e9;
	x_max = -1e9;
	while (i < 3)
	{
		a[0] = pts[i];
		a[1] = pts[(i + 1) % 3];
		if ((y >= fmin(a[0].y, a[1].y)) && (y <= fmax(a[0].y, a[1].y)))
		{
			b[0] = (y - a[0].y) / (a[1].y - a[0].y + 1e-10);
			b[1] = a[0].x + b[0] * (a[1].x - a[0].x);
			if (b[1] < x_min)
				x_min = b[1];
			if (b[1] > x_max)
				x_max = b[1];
		}
		i++;
	}
	draw_scanline(data, y, x_min, x_max);
}

void	draw_player_triangle(t_data *data, t_minimap *map, int size)
{
	t_dot	tip;
	t_dot	left;
	t_dot	right;
	t_dot	pts[3];
	int		y;

	tip.x = map->center_x + cos(data->player.angle) * size;
	tip.y = map->center_y + sin(data->player.angle) * size;
	left.x = map->center_x + cos(data->player.angle + 2.0944) * size * 0.6;
	left.y = map->center_y + sin(data->player.angle + 2.0944) * size * 0.6;
	right.x = map->center_x + cos(data->player.angle - 2.0944) * size * 0.6;
	right.y = map->center_y + sin(data->player.angle - 2.0944) * size * 0.6;
	pts[0] = tip;
	pts[1] = left;
	pts[2] = right;
	y = (int)fmin(fmin(tip.y, left.y), right.y);
	while (y <= (int)fmax(fmax(tip.y, left.y), right.y))
	{
		draw_triangle_line(data, pts, y);
		y++;
	}
}
