/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 21:12:21 by arocca            #+#    #+#             */
/*   Updated: 2025/10/13 17:08:48 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include "config.h"

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

static void	add_queue(t_bfs *bfs, t_point cell, int width, int height)
{
	if (!in_bound(cell.x, cell.y, width, height))
		return ;
	bfs->queue[bfs->rear] = cell;
	bfs->rear = (bfs->rear + 1) % bfs->size;
}

static bool	breadth_first_search(t_bfs *bfs, char **map, int width, int height)
{
	t_point	curr;

	while (bfs->front != bfs->rear)
	{
		curr = bfs->queue[bfs->front];
		bfs->front = (bfs->front + 1) % bfs->size;
		if (in_str(map[curr.y][curr.x], "1VNSEW", false))
			continue ;
		else if (map[curr.y][curr.x] != '0')
			return (err(BFS_ERR));
		map[curr.y][curr.x] = 'V';
		add_queue(bfs, (t_point){curr.x + 1, curr.y}, width, height);
		add_queue(bfs, (t_point){curr.x - 1, curr.y}, width, height);
		add_queue(bfs, (t_point){curr.x, curr.y + 1}, width, height);
		add_queue(bfs, (t_point){curr.x, curr.y - 1}, width, height);
	}
	return (true);
}

static bool	find_cell(char **map, t_point *cell)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				cell->x = j;
				cell->y = i;
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}

bool	init_bfs(char **map, int width, int height)
{
	t_bfs	*bfs;
	t_point	start;
	bool	result;

	result = true;
	info(BFS_START, CFG_LOG, NULL);
	bfs = create_bfs(width * height);
	if (!bfs)
		return (err(BFS_INIT_ERR));
	while (find_cell(map, &start))
	{
		if (start.x < 0 || start.y < 0 || start.x >= width || start.y >= height)
		{
			result = err(BFS_CELL_ERR);
			break ;
		}
		bfs->queue[bfs->rear++] = start;
		result = breadth_first_search(bfs, map, width, height);
		if (!result)
			break ;
	}
	free(bfs->queue);
	free(bfs);
	return (result);
}
