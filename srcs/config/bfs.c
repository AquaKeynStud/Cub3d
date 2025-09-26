/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 21:12:21 by arocca            #+#    #+#             */
/*   Updated: 2025/09/26 09:58:20 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "libft.h"

static t_bfs	*create_bfs(int size)
{
	t_bfs	*bfs;

	bfs = (t_bfs *)ft_calloc(1, sizeof(t_bfs));
	if (!bfs)
		return (NULL);
	bfs->size = size + 1;
	bfs->queue = (t_point *)ft_calloc(bfs->size, sizeof(t_point));
	if (!bfs->queue)
	{
		free(bfs);
		return (NULL);
	}
	return (bfs);
}

void	add_queue(t_bfs *bfs, t_point cell)
{
	bfs->queue[bfs->rear] = cell;
	bfs->rear = (bfs->rear + 1) % bfs->size;
}

bool	breadth_first_search(t_map *map, t_point cell)
{
	t_bfs	*bfs;
	t_point	curr;

	bfs = create_bfs(map->width * map->height);
	if (!bfs)
		return (err("Failed to initialize map verification"));
	bfs->queue[bfs->rear++] = cell;
	while (bfs->front != bfs->rear)
	{
		curr = bfs->queue[bfs->front];
		bfs->front = (bfs->front + 1) % bfs->size;
		if (in_str(map->map[curr.y][curr.x], "1V", false))
			continue ;
		else if (map->map[curr.y][curr.x] != ' ')
			return (err("Map must be surrounded by walls"));
		map->map[curr.y][curr.x] = 'V';
		add_queue(bfs, (t_point){curr.x + 1, curr.y});
		add_queue(bfs, (t_point){curr.x - 1, curr.y});
		add_queue(bfs, (t_point){curr.x, curr.y + 1});
		add_queue(bfs, (t_point){curr.x, curr.y - 1});
	}
	free(bfs->queue);
	free(bfs);
	return (true);
}

t_point	find_space(char **map)
{
	int		i;
	int		j;

	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				return ((t_point){i, j});
			j++;
		}
		i++;
	}
	return ((t_point){-1, -1});
}

bool	init_bfs(t_map *map)
{
	t_bfs	*bfs;

	bfs = create_bfs(map->width * map->height);
	if (!bfs)
		return (err("Failed to initialize map verification"));
	
}