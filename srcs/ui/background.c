/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:03:08 by arocca            #+#    #+#             */
/*   Updated: 2025/10/22 14:27:29 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "cub.h"
#include <math.h>

static int	get_bg_color(t_txts txt, float height, int center, int y)
{
	float	factor;

	factor = (float)abs(center - y);
	if (factor <= (height / BG_FADE_SPREAD))
		factor *= 1.0f / (height / BG_FADE_SPREAD);
	else
		factor = 1.0f;
	if (y >= center)
		return (apply_fog(txt.ceiling, factor));
	return (apply_fog(txt.floor, factor));
}

void	create_background(t_data *data, t_txts txt)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < data->win_h)
	{
		x = 0;
		color = get_bg_color(txt, (float)data->win_h, (data->win_h / 2.0f), y);
		while (x < data->win_w)
			data->bg.addr[y * data->bg.plen + x++] = color;
		y++;
	}
}
