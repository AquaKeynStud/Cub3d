/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:10:31 by arocca            #+#    #+#             */
/*   Updated: 2025/11/01 12:06:05 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <math.h>
#include <sys/time.h>

double	rad(double deg)
{
	return (deg * (PI / 180));
}

double	deg(double rad)
{
	return (rad * (180 / PI));
}

bool	in_bound(int x, int y, int width, int height)
{
	return (x >= 0 && x < width && y >= 0 && y < height);
}

double	clamp(double x, int min, int max)
{
	if (x < (double)min)
		return ((double)min);
	if (x > (double)max)
		return ((double)max);
	return (x);
}

long	get_tick_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}
