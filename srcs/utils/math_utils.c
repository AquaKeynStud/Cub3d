/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:10:31 by arocca            #+#    #+#             */
/*   Updated: 2025/10/15 18:47:25 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <math.h>

double	rad(double deg)
{
	return (deg * (PI / 180));
}

double	deg(double rad)
{
	return (rad * (180 / PI));
}

double	norm(double angle)
{
	angle = fmod(angle, (2 * PI));
	if (angle < 0)
		angle += (2 * PI);
	return (angle);
}

bool	in_bound(int x, int y, int width, int height)
{
	return (x >= 0 && x < width && y >= 0 && y < height);
}

int	clamp(double x, int min, int max)
{
	if (x < (double)min)
		return ((double)min);
	if (x > (double)max)
		return ((double)max);
	return (x);
}
