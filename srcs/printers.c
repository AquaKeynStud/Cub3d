/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 22:05:31 by arocca            #+#    #+#             */
/*   Updated: 2025/09/22 15:26:40 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	print_color(int	rgb)
{
	printf("Floor color -> R:%d G:%d B:%d\n",
		(rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, rgb & 0xFF);
}

void    debug_assets(t_data *data)
{
    printf("=== ASSETS DEBUG ===\n");

    printf("EAST   -> img:%p, w:%d, h:%d\n",
        data->assets.east.img,
        data->assets.east.width,
        data->assets.east.height);

    printf("WEST   -> img:%p, w:%d, h:%d\n",
        data->assets.west.img,
        data->assets.west.width,
        data->assets.west.height);

    printf("SOUTH  -> img:%p, w:%d, h:%d\n",
        data->assets.south.img,
        data->assets.south.width,
        data->assets.south.height);

    printf("NORTH  -> img:%p, w:%d, h:%d\n",
        data->assets.north.img,
        data->assets.north.width,
        data->assets.north.height);

	print_color(data->assets.floor);
	print_color(data->assets.ceiling);
}

void	debug(char *message, char *str)
{
	if (str && *str)
	{
		ft_printf("\e[1;31m📛 DEBUG - ");
		ft_printf(message, str);
		ft_printf(" 📛\e[0m\n");
	}
	else
		ft_printf("\e[1;31m📛 DEBUG - %s 📛\e[0m\n", message);
}