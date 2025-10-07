/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:27:02 by arocca            #+#    #+#             */
/*   Updated: 2025/10/07 16:19:04 by arocca           ###   ########.fr       */
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

static bool	normalize_map(char **map, int unit)
{
	int		i;
	int		pos;
	char	*tmp;

	i = 0;
	while (map[i])
	{
		pos = (int)ft_strlen(map[i]);
		if (pos > 0 && map[i][pos - 1] == '\n')
			map[i][--pos] = '\0';
		if (pos < unit)
		{
			tmp = (char *)ft_realloc(map[i], pos + 1, unit + 1);
			if (!tmp)
				return (err("Failed to normalize the map"));
			map[i] = tmp;
			while (pos < unit)
				map[i][pos++] = ' ';
			map[i][pos] = '\0';
		}
		i++;
	}
	return (true);
}

bool	configure_map(t_map *map_data)
{
	char	**map;
	int		xlen;
	int		ylen;

	map = map_data->map;
	get_map_size(map, &map_data->width, &map_data->height);
	xlen = map_data->width;
	ylen = map_data->height;
	if (!normalize_map(map, xlen) || !check_map_content(map))
		return (false);
	if (!init_bfs(map, xlen, ylen))
		return (false);
	print_map(map, print_verification);
	if (!ew_walls(map) || !ns_walls(map, xlen, ylen))
		return (err(BFS_ERR));
	reset_after_bfs(map);
	if (check_player_nb(map) != 1)
		return (err("The map must contain 1 player (max)"));
	return (true);
}
