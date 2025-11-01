/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:53:17 by arocca            #+#    #+#             */
/*   Updated: 2025/11/01 10:28:53 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include <sys/time.h>

long	get_tick_time(void)
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL) == -1)
        return (-1);
    return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

bool	add_door(t_data *data, t_door **doors, int y, int x)
{
	t_door	*new_door;
	t_door	*current;

	new_door = ft_calloc(1, sizeof(t_door));
	if (!new_door)
		return (false);
	if (!new_image(&new_door->texture, data->mlx,
			data->assets.door.width, data->assets.door.height))
		return (false);
	copy_image(data, &new_door->texture, &data->assets.door);
	new_door->pos.y = y;
	new_door->pos.x = x;
	new_door->tick = get_tick_time();
	if (new_door->tick == -1)
		return (false);
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

bool	is_door_open(t_door *doors, int y, int x)
{
	t_door	*door;

	door = get_door(doors, y, x);
	if (door)
		return (door->open);
	return (false);
}

bool	free_all_doors(t_data *data, t_door **doors)
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
					return (free_all_doors(data, doors));
			x++;
		}
		y++;
	}
	return (true);
}
