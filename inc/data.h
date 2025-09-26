/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:54:57 by arocca            #+#    #+#             */
/*   Updated: 2025/09/26 21:18:01 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

/* -- Includes -- */

/* -- Structures -- */
typedef struct s_image
{
	int		bpp;
	int		slen;
	void	*img;
	char	*addr;
	int		width;
	int		endian;
	int		height;
}			t_image;

typedef struct s_txts
{
	t_image	west;
	t_image	east;
	t_image	north;
	t_image	south;
	int		floor;
	int		ceiling;
}			t_txts;

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
}			t_map;

typedef struct s_point
{
	int		x;
	int		y;
}			t_point;

typedef struct s_bfs
{
	int		size;
	int		rear;
	int		front;
	t_point	*queue;
}			t_bfs;

#endif