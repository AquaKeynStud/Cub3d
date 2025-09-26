/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:27:02 by arocca            #+#    #+#             */
/*   Updated: 2025/09/26 21:21:54 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"

static void	get_map_size(char **map, int *width, int *height)
{
	int	len;

	(*height) = 0;
	*width = ft_strlen(map[0]);
	if (*width > 0 && map[0][*width - 1] == '\n')
		(*width)--;
	while (map[(*height)])
	{
		len = (int)ft_strlen(map[(*height)]);
		if (map[*height][len - 1] == '\n')
			len--;
		if (len > (*width))
			(*width) = len;
		(*height)++;
	}
}

static void	normalize_map(char **map, int unit)
{
	int	i;
	int	pos;

	i = 0;
	while (map[i])
	{
		pos = (int)ft_strlen(map[i]);
		if (pos > 0 && map[i][pos - 1] == '\n')
		{
			map[i][pos - 1] = '\0';
			pos--;
		}
		if (pos < unit)
		{
			map[i] = (char *)ft_realloc(map[i], pos + 1, unit + 1);
			while (pos < unit)
				map[i][pos++] = ' ';
			map[i][pos] = '\0';
		}
		i++;
	}
}

static void	reset_after_bfs(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'V')
				map[i][j] = ' ';
			j++;
		}
		i++;
	}
}

static bool	check_player_nb(char **map)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	count = 0;
	if (!map || !*map)
		return (-1);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
					|| map[i][j] == 'W' || map[i][j] == 'E')
				count += 1;
			j++;
		}
		i++;
	}
	return (count == 1);
}

bool	configure_map(t_map *map)
{
	get_map_size(map->map, &map->width, &map->height);
	normalize_map(map->map, map->width);
	if (!init_bfs(map->map, map->width, map->height))
		return (false);
	reset_after_bfs(map->map);
	if (check_player_nb(map->map) != 1)
		return (err("Only one player is allowed on the map"));
	return (true);
}
