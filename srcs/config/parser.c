/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:05:20 by arocca            #+#    #+#             */
/*   Updated: 2025/10/17 12:43:05 by abouclie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <math.h>
#include "libft.h"
#include "config.h"

bool	check_map_content(char **map, t_player player)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!in_str(map[i][j], "01NSEW ", false))
			{
				print_map(map, player, print_type);
				return (err(MAP_TYPE_ERR));
			}
			j++;
		}
		i++;
	}
	return (true);
}

static void	init_player_data(t_player *player, int i, int j, char dir)
{
	player->x = j + 0.5f;
	player->y = i + 0.5f;
	player->cam_fov = tan(rad(FOV) / 2.0);
	player->ori.x = (dir == 'E') - (dir == 'W');
	player->ori.y = (dir == 'S') - (dir == 'N');
	player->angle = atan2(player->ori.y, player->ori.x);
	player->cam.x = -player->ori.y * player->cam_fov;
	player->cam.y = player->ori.x * player->cam_fov;
	player_infos(*player, dir);
}

bool	get_player(char **map, t_player *player)
{
	int		i;
	int		j;
	bool	debounce;

	i = 0;
	debounce = false;
	info(PLR_START, CFG_LOG, NULL);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (in_str(map[i][j], "NSEW", false))
			{
				if (debounce)
					return (err(MANY_PLAYER_ERR));
				init_player_data(player, i, j, map[i][j]);
				debounce = map[i][j];
				map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	return (debounce || err(NO_PLAYER_ERR));
}

bool	east_west_walls(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = ft_strlen(map[i]) - 1;
		while (j >= 0 && map[i][j] && map[i][j] == ' ')
			j--;
		if (j >= 0 && (!map[i][j] || map[i][j] != '1'))
			return (false);
		j = 0;
		while (j < (int)ft_strlen(map[i]) && map[i][j] && map[i][j] == ' ')
			j++;
		if (j >= 0 && (!map[i][j] || map[i][j] != '1'))
			return (false);
		i++;
	}
	return (true);
}

bool	south_north_walls(char **map, int width, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < width)
	{
		j = height - 1;
		while (j >= 0 && map[j][i] && map[j][i] == ' ')
			j--;
		if (j >= 0 && (!map[j][i] || map[j][i] != '1'))
			return (false);
		j = 0;
		while (j < height && map[j][i] && map[j][i] == ' ')
			j++;
		if (j < height && (!map[j][i] || map[j][i] != '1'))
			return (false);
		i++;
	}
	return (true);
}
