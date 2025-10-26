/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:12:07 by arocca            #+#    #+#             */
/*   Updated: 2025/10/26 11:58:36 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "cub.h"
#include <math.h>

static t_image	get_img_column(t_txts *txts, t_ray ray, t_idot *txt)
{
	t_image	img;

	if (ray.door)
		img = txts->door;
	else if (ray.side && ray.dir.y <= 0)
		img = txts->north;
	else if (ray.side && ray.dir.y > 0)
		img = txts->south;
	else if (!ray.side && ray.dir.x <= 0)
		img = txts->west;
	else if (!ray.side && ray.dir.x > 0)
		img = txts->east;
	txt->x = (int)clamp(ray.pos * (double)img.width, 0, img.width);
	if ((!ray.side && ray.dir.x > 0) || (ray.side && ray.dir.y <= 0))
		txt->x = img.width - txt->x - 1;
	return (img);
}

static t_txt_col	get_column_data(t_data *data, t_ray ray, t_image img, int x)
{
	t_txt_col	c;

	c.x = x;
	c.wall_h = (int)((double)data->win_h / ray.dist);
	c.start = data->win_h / 2 - c.wall_h / 2;
	c.end = c.start + c.wall_h;
	c.start = (int)clamp((double)c.start, 0, data->win_h / 2);
	c.end = (int)clamp((double)c.end, data->win_h / 2, data->win_h - 1);
	c.y_step = 0;
	if (c.wall_h != 0)
		c.y_step = (double)img.height / (double)c.wall_h;
	c.txt_pos = (c.start - data->win_h / 2.0 + c.wall_h / 2.0) * c.y_step;
	c.fog = get_fog(data->assets.fog, ray.dist, data->assets.fog_unit);
	c.alpha = get_alpha(data->assets.alpha, ray.dist, data->assets.alpha_unit);
	return (c);
}

void	display_texture(t_data *data, t_txt_col col, t_image img, t_idot txt)
{
	int	y;
	int	*dst;
	int	color;

	y = col.start;
	dst = data->dsp.addr + y * data->dsp.plen + col.x;
	while (y < col.end)
	{
		txt.y = col.txt_pos;
		col.txt_pos += col.y_step;
		color = img.addr[txt.y * img.plen + (int)txt.x];
		color = apply_fog(color, col.fog);
		*dst = color;
		y++;
		dst += data->dsp.plen;
	}
}

void	display_fogged(t_data *data, t_txt_col col, int color)
{
	int	y;
	int	bg;
	int	*dst;

	y = col.start;
	dst = data->dsp.addr + y * data->dsp.plen + col.x;
	while (y < col.end)
	{
		bg = *dst;
		color = apply_fog(color, col.fog);
		color = distance_blur(color, bg, col.alpha);
		*dst = color;
		y++;
		dst += data->dsp.plen;
	}
}

void	display_wall(t_data *data, t_ray ray, int x)
{
	t_idot		txt;
	t_image		img;
	t_txt_col	column;

	img = get_img_column(&data->assets, ray, &txt);
	if (!img.img)
		return ;
	column = get_column_data(data, ray, img, x);
	if (!column.fog)
		display_fogged(data, column, 0x000000);
	else
		display_texture(data, column, img, txt);
}
