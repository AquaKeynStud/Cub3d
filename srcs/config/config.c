/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:27:02 by arocca            #+#    #+#             */
/*   Updated: 2025/10/24 12:09:03 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include "config.h"

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
	info(NORM_START, CFG_LOG, NULL);
	while (map[i])
	{
		pos = (int)ft_strlen(map[i]);
		if (pos > 0 && map[i][pos - 1] == '\n')
			map[i][--pos] = '\0';
		if (pos < unit)
		{
			tmp = (char *)ft_realloc(map[i], pos + 1, unit + 1);
			if (!tmp)
				return (err(MAP_NORM_ERR));
			map[i] = tmp;
			while (pos < unit)
				map[i][pos++] = ' ';
			map[i][pos] = '\0';
		}
		i++;
	}
	return (true);
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
				map[i][j] = '0';
			j++;
		}
		i++;
	}
}

bool	configure(t_data *data, t_map *map_data)
{
	char	**map;
	int		xlen;
	int		ylen;

	map = map_data->map;
	info(CFG_START, CFG_LOG, NULL);
	get_map_size(map, &map_data->width, &map_data->height);
	xlen = map_data->width;
	ylen = map_data->height;
	info(PSG_START, CFG_LOG, NULL);
	if (!normalize_map(map, xlen) || !check_map_content(map, data->player))
		return (false);
	if (!get_player(map, &data->player))
		return (false);
	if (!init_bfs(map, xlen, ylen) || !east_west_walls(map)
		|| !south_north_walls(map, xlen, ylen))
		return (err(BFS_ERR));
	print_map(map, data->player, print_verification);
	reset_after_bfs(map);
	info(CFG_END, CFG_LOG, NULL);
	print_map(map, data->player, print_type);
	return (true);
}
