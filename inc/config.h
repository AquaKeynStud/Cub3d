/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:56:17 by arocca            #+#    #+#             */
/*   Updated: 2025/10/08 11:56:39 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

/* -- Includes -- */
# include "data.h"

/* -- Structures -- */
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

/* -- Parsing Info Messages -- */
# define CFG_LOG	"\t\e[107;1;38;5;75m     "
# define CFG_END	"%s🎋 Data configured successfully ! 💮%s"
# define CFG_START	"%s🗺️  Starting configuration of the map 🌐%s"
# define NORM_START	"%s🍱 Normalization of the map... 🎐%s"
# define BFS_START	"%s🥡 Processing BFS verification... 🦈%s"
# define PSG_START	"%s🗼 Verifying map syntax... ⛲️ %s"

/* -- Error Messages -- */
# define BFS_ERR		"⚗️  Map must be surrounded by walls 🎑"
# define BFS_INIT_ERR	"🛟 Failed to initialize map verification 🐡"
# define BFS_CELL_ERR	"🚧 Error while checking map borders; aborting... 🚈"

# define MAP_TYPE_ERR	"🍄 Invalid type in map 🍃"
# define MAP_NORM_ERR	"🍱 Failed to normalize the map 🫚"

# define NO_PLAYER_ERR		"🎎 The map must contain at least 1 player 🀄️"
# define MANY_PLAYER_ERR	"🍇 The map cannot contain more than 1 player 🫐"

/* -- Format Functions -- */
void	debug_assets(t_txts txts);
void	reset_after_bfs(char **map);

/* -- Parsing Functions -- */
bool	east_west_walls(char **map);
int		check_player_nb(char **map);
bool	check_map_content(char **map);
bool	init_bfs(char **map, int width, int height);
bool	south_north_walls(char **map, int width, int height);

/* -- Config Main Function -- */
bool	configure_map(t_map *map);

#endif