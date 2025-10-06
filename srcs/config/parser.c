/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:05:20 by arocca            #+#    #+#             */
/*   Updated: 2025/10/03 16:25:57 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"

bool	check_map_content(char **map)
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
				return (err("Invalid type in map"));
			j++;
		}
		i++;
	}
	return (true);
}

bool	check_player_nb(char **map)
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

void	reset_after_bfs(char **map)
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
