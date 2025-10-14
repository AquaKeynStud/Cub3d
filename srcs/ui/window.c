/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:53:04 by arocca            #+#    #+#             */
/*   Updated: 2025/10/14 10:49:39 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "ft_printf.h"

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
