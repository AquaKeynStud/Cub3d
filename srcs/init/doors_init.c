/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:53:17 by arocca            #+#    #+#             */
/*   Updated: 2025/11/05 12:14:27 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"

static bool	free_door(t_data *data, t_door *new)
{
	if (new->texture.img)
		mlx_destroy_image(data->mlx, new->texture.img);
	free(new);
	return (false);
}

bool	add_door(t_data *data, t_door **doors, int y, int x)
{
	t_door	*new_door;
	t_door	*current;

	new_door = ft_calloc(1, sizeof(t_door));
	if (!new_door)
		return (free_door(data, new_door));
	if (!new_image(&new_door->texture, data->mlx,
			data->assets.door.width, data->assets.door.height))
		return (free_door(data, new_door));
	copy_image(data, &new_door->texture, &data->assets.door);
	new_door->pos.y = y;
	new_door->pos.x = x;
	new_door->tick = get_tick_time();
	if (new_door->tick == -1)
		return (free_door(data, new_door));
	if (!*doors)
	{
		*doors = new_door;
		return (true);
	}
	current = *doors;
	while (current->next)
		current = current->next;
	current->next = new_door;
	return (true);
}

t_door	*get_door(t_door *doors, int y, int x)
{
	while (doors)
	{
		if (doors->pos.y == y && doors->pos.x == x)
			return (doors);
		doors = doors->next;
	}
	return (NULL);
}

bool	door_open(t_door *doors, int y, int x)
{
	t_door	*door;

	door = get_door(doors, y, x);
	if (door)
		return (door->open);
	return (false);
}

bool	init_doors(t_data *data, t_door **doors, char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'D' && !add_door(data, doors, y, x))
				return (free_doors(data, doors));
			x++;
		}
		y++;
	}
	return (true);
}
