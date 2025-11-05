/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:56:17 by arocca            #+#    #+#             */
/*   Updated: 2025/11/05 11:28:17 by arocca           ###   ########.fr       */
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
# define CFG_END	"🎋 Data configured successfully ! 💮"
# define CFG_START	"🗺️  Starting configuration of the map 🌐"
# define NORM_START	"🍱 Normalization of the map... 🎐"
# define BFS_START	"🥡 Processing BFS verification... 🦈"
# define PSG_START	"🗼 Starting verification of map syntax... ⛲️"
# define PLR_START	"🍥 Getting player informations... 🍙"

/* -- Error Messages -- */
# define BFS_ERR		"⚗️  Map must be surrounded by walls 🎑"
# define BFS_INIT_ERR	"🛟 Failed to initialize map verification 🐡"
# define BFS_CELL_ERR	"🚧 Error while checking map borders; aborting... 🚈"

# define MAP_TYPE_ERR	"🍄 Invalid type in map 🍃"
# define MAP_NORM_ERR	"🍱 Failed to normalize the map 🫚"

# define NO_PLAYER_ERR		"🎎 The map must contain at least 1 player 🀄️"
# define MANY_PLAYER_ERR	"🍇 Several players have been detected on map 🫐"

/* -- Parsing Functions -- */
bool	east_west_walls(char **map);
bool	get_player(char **map, t_player *player);
bool	init_bfs(char **map, int width, int height);
bool	south_north_walls(char **map, int width, int height);
bool	check_map_content(char **map, t_player player);

/* -- Config Main Function -- */
bool	configure(t_data *data, t_map *map_data);

#endif