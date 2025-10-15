/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:12:07 by arocca            #+#    #+#             */
/*   Updated: 2025/10/15 18:46:42 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "cub.h"

static t_image	get_img_column(t_txts *txts, t_ray ray, t_dot *txt)
{
	t_image	img;

	if (ray.side && ray.dir.y <= 0)
		img = txts->north;
	else if (ray.side && ray.dir.y > 0)
		img = txts->south;
	else if (!ray.side && ray.dir.x <= 0)
		img = txts->west;
	else if (!ray.side && ray.dir.x > 0)
		img = txts->east;
	txt->x = clamp(ray.pos * (double)img.width, 0, img.width);
	if ((!ray.side && ray.dir.x > 0) || (ray.side && ray.dir.y <= 0))
		txt->x = img.width - txt->x - 1;
	return (img);
}

static t_txt_col	get_column_range(t_data *data, t_ray ray, t_image img)
{
	t_txt_col	c;

	c.line_len = (int)((double)data->win_h / ray.magnitude);
	c.start = data->win_h / 2 - c.line_len / 2;
	c.end = data->win_h / 2 + c.line_len / 2;
	c.start = clamp((double)c.start, 0, data->win_h / 2);
	c.end = clamp((double)c.end, data->win_h / 2, data->win_h - 1);
	c.y_step = (double)img.height / (double)c.line_len;
	c.txt_pos = (c.start - data->win_h / 2.0 + c.line_len / 2.0) * c.y_step;
	return (c);
}

void	display_background(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->win_w)
	{
		y = 0;
		while (y < data->win_h / 2)
			put_pixel(&data->screen, x, y++, data->assets.floor);
		while (y < data->win_h)
			put_pixel(&data->screen, x, y++, data->assets.ceiling);
		x++;
	}
}

void	display_wall(t_data *data, t_ray ray, int x)
{
	int			y;
	t_dot		txt;
	t_image		img;
	int			color;
	t_txt_col	column;

	img = get_img_column(&data->assets, ray, &txt);
	column = get_column_range(data, ray, img);
	y = column.start;
	while (y < column.end)
	{
		txt.y = clamp(column.txt_pos, 0, img.height - 1);
		column.txt_pos += column.y_step;
		color = get_pixel(&img, txt.x, txt.y);
		put_pixel(&data->screen, x, y++, color);
	}
}
