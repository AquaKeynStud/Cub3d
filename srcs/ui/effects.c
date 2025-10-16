/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:35:39 by arocca            #+#    #+#             */
/*   Updated: 2025/10/16 21:02:20 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "events.h"

int	apply_fog(int color, double dist)
{
	int		r;
	int		g;
	int		b;
	double	factor;

	if (dist > MIN_RENDER)
		dist = MIN_RENDER;
	factor = 1.0 - (dist / MIN_RENDER);
	factor *= (factor > 0.0);
	if (factor > 1.0)
		factor = 1.0;
	r = ((color >> 16) & 0xFF) * factor;
	g = ((color >> 8) & 0xFF) * factor;
	b = (color & 0xFF) * factor;
	return ((r << 16) | (g << 8) | b);
}

int	apply_fade(int color, double factor)
{
	int		r;
	int		g;
	int		b;

	factor *= (factor > 0.0);
	if (factor > 1.0)
		factor = 1.0;
	r = ((color >> 16) & 0xFF) * factor;
	g = ((color >> 8) & 0xFF) * factor;
	b = (color & 0xFF) * factor;
	return ((r << 16) | (g << 8) | b);
}

int	distance_blur(double distance, int color, int bg)
{
	int		r;
	int		g;
	int		b;
	double	alpha;

	alpha = 1.0;
	if (distance < MIN_RENDER)
		return (color);
	else
		alpha -= (distance - MIN_RENDER) / (MAX_RENDER - MIN_RENDER);
	if (alpha >= 1.0)
		return (color);
	r = (int)(red(color) * alpha + red(bg) * (1 - alpha));
	b = (int)(blue(color) * alpha + blue(bg) * (1 - alpha));
	g = (int)(green(color) * alpha + green(bg) * (1 - alpha));
	return ((r << 16) | (g << 8) | b);
}
