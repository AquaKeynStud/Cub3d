/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_wrap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:53:04 by arocca            #+#    #+#             */
/*   Updated: 2025/11/05 12:18:58 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "cub.h"
#include "ft_printf.h"

int	end_loop(t_data *data)
{
	mlx_loop_end(data->mlx);
	return (0);
}

bool	new_image(t_image *image, void *mlx, int width, int height)
{
	if (!image || !mlx || width <= 0 || height <= 0)
		return (false);
	image->img = mlx_new_image(mlx, width, height);
	if (!image->img)
		return (err(MLX_IMG_ERR));
	image->addr = (int *)mlx_get_data_addr(
			image->img, &image->bpp, &image->slen, &image->endian);
	if (!image->addr)
	{
		mlx_destroy_image(mlx, image->img);
		return (err(IMG_ADDR_ERR));
	}
	image->width = width;
	image->height = height;
	image->plen = image->slen / (image->bpp / 8);
	return (true);
}

void	copy_image(t_data *data, t_image *dest, t_image *src)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	if (!data || !dest || !src || !dest->addr || !src->addr)
		return ;
	while (y < dest->height && y < src->height)
	{
		x = 0;
		while (x < dest->width && x < src->width)
		{
			color = src->addr[y * (src->slen / 4) + x];
			dest->addr[y * (dest->slen / 4) + x] = color;
			x++;
		}
		y++;
	}
}

t_image	get_image(t_data *data, char *path, char *ext)
{
	t_image	i;

	(void)ext;
	if (!has_ext(path, ".xpm"))
	{
		err_errno(path, INVALID_EXT, false);
		return ((t_image){0});
	}
	i.img = mlx_xpm_file_to_image(data->mlx, path, &i.width, &i.height);
	if (!i.img)
	{
		err_errno(path, NULL, false);
		return ((t_image){0});
	}
	i.addr = (int *)mlx_get_data_addr(i.img, &i.bpp, &i.slen, &i.endian);
	i.plen = i.slen / (i.bpp / 8);
	return (i);
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
	ft_printf(DSP_SIZE, INFO, width, height, EOL);
	return (true);
}
