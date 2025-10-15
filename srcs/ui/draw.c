/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:12:07 by arocca            #+#    #+#             */
/*   Updated: 2025/10/15 14:25:18 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->slen + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

void	get_wall(t_data *data, t_ray ray, int x)
{
	int	end;
	int	start;
	int	color;
	int	line_len;

	line_len = (int)(data->win_h / ray.magnitude);
	end = line_len / 2 + data->win_h / 2;
	start = -line_len / 2 + data->win_h / 2;
	if (ray.side)
		color = 0x0000FF;
	else
		color = 0x000088;
	if (start < 0)
		start = 0;
	if (end >= data->win_h)
		end = data->win_h - 1;
	for (int y = start; y <= end; y++)
		my_mlx_pixel_put(&data->screen, x, y, color);
}
