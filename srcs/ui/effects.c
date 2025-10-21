/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:35:39 by arocca            #+#    #+#             */
/*   Updated: 2025/10/21 17:55:36 by arocca           ###   ########.fr       */
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

int	apply_fade(int color, double factor)
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
