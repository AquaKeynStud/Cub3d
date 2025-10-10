/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:53:04 by arocca            #+#    #+#             */
/*   Updated: 2025/10/10 15:21:51 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "ft_printf.h"

bool	create_window(t_data *data, int width, int height, char *name)
{
	if (!width || !height)
		return (false);
	mlx_get_screen_size(data->mlx, &data->screen_width, &data->screen_height);
	if (width > data->screen_width || height > data->screen_height)
		return (false);
	if (width < 0)
		width = data->screen_width;
	if (height < 0)
		height = data->screen_height;
	data->win = mlx_new_window(data->mlx, width, height, name);
	if (!data->win)
		return (false);
	data->screen_width = width;
	data->screen_height = height;
	ft_printf("%s🗼 Window size : %ix%i 🚞%s", INFO, width, height, EOL);
	return (true);
}
