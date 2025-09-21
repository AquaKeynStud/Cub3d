/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:54:57 by arocca            #+#    #+#             */
/*   Updated: 2025/09/18 17:43:17 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/* -- Includes -- */

/* -- Structures -- */
typedef struct s_image {
	int		bpp;
	int		slen;
	void	*img;
	char	*addr;
	int		width;
	int		endian;
	int		height;
}   t_image;

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
	int	fd;
}			t_map;

#endif