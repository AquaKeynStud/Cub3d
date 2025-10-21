/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:53:04 by arocca            #+#    #+#             */
/*   Updated: 2025/10/21 18:06:56 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "cub.h"
#include "ft_printf.h"

static bool	new_image(t_image *image, void *mlx, int width, int height)
{
	if (!image || !mlx || width <= 0 || height <= 0)
		return (err("Invalid image creation parameters"));
	image->img = mlx_new_image(mlx, width, height);
	if (!image->img)
		return (err("Failed to create image with mlx"));
	image->addr = (int *)mlx_get_data_addr(
			image->img, &image->bpp, &image->slen, &image->endian);
	if (!image->addr)
	{
		mlx_destroy_image(mlx, image->img);
		return (err("Failed to get data addr for image"));
	}
	image->plen = image->slen / (image->bpp / 8);
	return (true);
}

bool	init_display_images(t_data *data)
{
	if (!new_image(&data->dsp, data->mlx, data->win_w, data->win_h))
		return (err("Failed to create display render image"));
	if (!new_image(&data->bg, data->mlx, data->win_w, data->win_h))
		return (err("Failed to create background render image"));
	create_background(data, data->assets);
	return (true);
}

bool	create_window(t_data *data, int width, int height, char *name)
{
	if (!width || !height)
		return (false);
	mlx_get_screen_size(data->mlx, &data->win_w, &data->win_h);
	if (width > data->win_w || height > data->win_h)
		return (false);
	if (width < 0)
		width = data->win_w;
	if (height < 0)
		height = data->win_h;
	data->win = mlx_new_window(data->mlx, width, height, name);
	if (!data->win)
		return (false);
	data->win_w = width;
	data->win_h = height;
	ft_printf("%s🗼 Window size : %ix%i 🚞%s", INFO, width, height, EOL);
	return (true);
}
