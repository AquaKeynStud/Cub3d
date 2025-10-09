/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:53:04 by arocca            #+#    #+#             */
/*   Updated: 2025/10/09 15:53:17 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "ft_printf.h"

bool	create_window(t_data *data, int width, int height, char *name)
{
	int	screen_width;
	int	screen_height;

	if (!width || !height)
		return (false);
	screen_width = 0;
	screen_height = 0;
	mlx_get_screen_size(data->mlx, &screen_width, &screen_height);
	if (width > screen_width || height > screen_height)
		return (false);
	if (width < 0)
		width = screen_width;
	if (height < 0)
		height = screen_height;
	data->win = mlx_new_window(data->mlx, width, height, name);
	if (!data->win)
		return (false);
	ft_printf("%s🗼 Window size : %ix%i 🚞%s", INFO, width, height, EOL);
	return (true);
}
