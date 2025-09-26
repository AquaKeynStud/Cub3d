/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:27:02 by arocca            #+#    #+#             */
/*   Updated: 2025/09/25 20:42:51 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"

void	get_map_size(char **map, int *width, int *height)
{
	(*height) = 0;
	(*width) = ft_strlen(*map);
	while (map[(*height)])
	{
		if ((int)ft_strlen(map[(*height)]) > (*width))
			(*width) = ft_strlen(map[(*height)]);
		(*height)++;
	}
}

void	normalize_map(char **map, int unit)
{
	int		i;
	int		pos;

	i = 0;
	while (map[i])
	{
		pos = (int)ft_strlen(map[i]);
		if (pos < unit)
		{
			map[i] = (char *)ft_realloc(map[i], pos + 1, unit + 1);
			while (pos < unit)
				map[i][pos++] = ' ';
			map[i][pos] = '\0';
		}
		else if (map[i][pos] == '\n')
			map[i][pos] = '\0';
		i++;
	}
}

void	configure_map(t_map *map)
{
	get_map_size(map->map, &map->width, &map->height);
	normalize_map(map->map, map->width);
}