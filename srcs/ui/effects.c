/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:35:39 by arocca            #+#    #+#             */
/*   Updated: 2025/10/24 11:43:34 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "events.h"

int	apply_fog(int color, float factor)
{
	int		r;
	int		g;
	int		b;

	r = red(color) * factor;
	b = blue(color) * factor;
	g = green(color) * factor;
	return ((r << 16) | (g << 8) | b);
}

int	distance_blur(int color, int bg, float alpha)
{
	int		r;
	int		g;
	int		b;

	if (alpha >= 1.0)
		return (color);
	r = (int)(red(color) * alpha + red(bg) * alpha);
	b = (int)(blue(color) * alpha + blue(bg) * alpha);
	g = (int)(green(color) * alpha + green(bg) * alpha);
	return ((r << 16) | (g << 8) | b);
}

void	display_crossair(t_data *data)
{
	int x;
	int y;
	int center_x;
	int center_y;

	if (CROSSAIR_SIZE == 0)
		return ;
	center_x = data->win_w / 2;
	center_y = data->win_h / 2;
	y = center_y - CROSSAIR_SIZE;
	while (y <= center_y + CROSSAIR_SIZE)
	{
		x = center_x - (CROSSAIR_SIZE - abs(center_y - y));
		while (x <= center_x + (CROSSAIR_SIZE - abs(center_y - y)))
			data->dsp.addr[y * data->dsp.plen + x++] = CROSSAIR_COLOR;
		y++;
	}
}

void	display_sprint(t_data *data, t_sprint s)
{
	int	x;
	int	y;
	int	ratio;
	int	pixel;
	int	stam_width;

	y = s.start.y - 1;
	ratio = (data->player.stamina * 255) / MAX_STAMINA;
	stam_width = (data->player.stamina * s.len.x) / MAX_STAMINA;
	while (y++ <= s.start.y + s.len.y)
	{
		x = s.start.x - 1;
		while (x++ <= s.start.x + s.len.x)
		{
			pixel = y * data->dsp.plen + x;
			if (y == s.start.y || y > s.start.y + s.len.y)
				data->dsp.addr[pixel] = 0XFFFFFF;
			else if (x > s.start.x && x < s.start.x + stam_width)
				data->dsp.addr[pixel] = ((255 - ratio) << 16) | (ratio << 8);
			else if (x >= s.start.x + stam_width && x < s.start.x + s.len.x)
				data->dsp.addr[pixel] = 0x202020;
			else
				data->dsp.addr[pixel] = 0XFFFFFF;
		}
	}
}
