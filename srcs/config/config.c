/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:27:02 by arocca            #+#    #+#             */
/*   Updated: 2025/10/09 16:39:45 by arocca           ###   ########.fr       */
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

static bool	init_player_data(t_player *player, char dir)
{
	
}

static bool	get_player(char **map, t_player *player)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (in_str(map[i][j], "NSEW", false))
			{
				player->x = j + 0.5;
				player->y = i + 0.5;
				player->cam_x = (map[i][j] == 'E') - (map[i][j] == 'W');
				player->cam_y = (map[i][j] == 'S') - (map[i][j] == 'N');
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}

bool	configure_map(t_map *map_data)
{
	char	**map;
	int		xlen;
	int		ylen;

	map = map_data->map;
	info(CFG_START, CFG_LOG, NULL);
	get_map_size(map, &map_data->width, &map_data->height);
	xlen = map_data->width;
	ylen = map_data->height;
	if (!normalize_map(map, xlen) || !check_map_content(map)
		|| !init_bfs(map, xlen, ylen))
		return (false);
	print_map(map, print_verification);
	if (!east_west_walls(map) || !south_north_walls(map, xlen, ylen))
		return (err(BFS_ERR));
	reset_after_bfs(map);
	info(PSG_START, CFG_LOG, NULL);
	if (check_player_nb(map) > 1)
		return (err(MANY_PLAYER_ERR));
	else if (check_player_nb(map) < 1)
		return (err(NO_PLAYER_ERR));
	info(CFG_END, CFG_LOG, NULL);
	return (true);
}
