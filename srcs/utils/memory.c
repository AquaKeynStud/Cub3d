/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 10:57:56 by arocca            #+#    #+#             */
/*   Updated: 2025/11/01 11:39:17 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"

bool	free_doors(t_data *data, t_door **doors)
{
	t_door	*next;
	t_door	*current;

	if (!doors || !*doors)
		return (false);
	current = *doors;
	while (current)
	{
		next = current->next;
		if (current->texture.img)
			mlx_destroy_image(data->mlx, current->texture.img);
		free(current);
		current = next;
	}
	*doors = NULL;
	return (false);
}

static void	free_images(t_data *data, t_txts *assets)
{
	int	i;

	i = 0;
	if (assets->east.img)
		mlx_destroy_image(data->mlx, assets->east.img);
	if (assets->west.img)
		mlx_destroy_image(data->mlx, assets->west.img);
	if (assets->south.img)
		mlx_destroy_image(data->mlx, assets->south.img);
	if (assets->north.img)
		mlx_destroy_image(data->mlx, assets->north.img);
	if (assets->door.img)
		mlx_destroy_image(data->mlx, assets->door.img);
	if (data->file.has_door)
	{
		while (i < 5)
			mlx_destroy_image(data->mlx, assets->d_anim[i++].img);
		free_doors(data, &assets->doors);
	}
	if (data->dsp.img)
		mlx_destroy_image(data->mlx, data->dsp.img);
	if (data->bg.img)
		mlx_destroy_image(data->mlx, data->bg.img);
}

void	clean_exit(t_data *data, int code)
{
	free_images(data, &data->assets);
	if (data->map.map)
		double_free((void **)data->map.map, 0);
	if (data->assets.fog)
		free(data->assets.fog);
	if (data->assets.alpha)
		free(data->assets.alpha);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(code);
}
