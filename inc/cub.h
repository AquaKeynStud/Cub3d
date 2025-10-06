/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:06:13 by arocca            #+#    #+#             */
/*   Updated: 2025/10/03 16:26:07 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

/* -- Includes -- */
# include "mlx.h"
# include "data.h"
# include <stdbool.h>
# include "mlx_int.h"

/* -- Structures -- */
typedef struct s_file
{
	int	fd;
	int	nl;
	int	pos;
	int	cap;
	int	line_nb;
}			t_file;

typedef struct s_data
{
	t_map	map;
	void	*mlx;
	void	*win;
	t_file	file;
	t_txts	assets;
}			t_data;

/* -- Input Macros -- */
# define KEY_W 122 // 119
# define KEY_A 113 // 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

/* -- Error Reports Macros -- */
# define EOL		"     \e[0m\n"
# define ERROR		"\t\e[107;1;31m     🏮 Error: "
# define ERRNOLOG	"\e[1;38;5;203m🈲    %s: %s    🈲\e[0m\n"
# define USAGE_ERR		"\e[1;31m😾 Usage: %s <path_to_map.cub> 😾\e[0m\n"
# define WALL_IMG_ERR	"🪾  Failed to initialize %s wall image 🍂"
# define COLOR_IMG_ERR	"🌈 No color found for %s 🍡"

/* -- Info Reports Macros -- */
# define MAPLOG		"\t\e[107;1;38;5;210m     "
# define INFO		"\t\e[107;1;34m     🗻 Info: "
# define TOPBAND	"\n\t\e[1;35m꧁  ⟣──╼━━━━ﾒ %s ﾒ━━━━╾──⟢ ꧂  \e[0m\n"
# define BOTTOMBAND	"\t\e[1;35m%s꧁  ⟣──╼━━━ﾒ %s - %s ﾒ━━━╾──⟢ ꧂  \e[0m\n\n"

/* -- Logs Functions -- */
void	print_header(void);

/* -- File Functions -- */
bool	parse_param(t_data *data, char *line);
bool	has_ext(const char *filename, char *ext);
bool	get_info_from_file(t_data *data, const char *filename);
bool	parse_map(char ***map, char *line, int *pos, int *cap);

/* -- Display Functions -- */
bool	create_window(t_data *data, int width, int height, char *name);

bool	configure_map(t_map *map);
bool	init_bfs(char **map, int width, int height);

/* -- Errors Functions -- */
bool	err(char *msg);
bool	err_errno(char *msg);
bool	err_str(char *msg, char *str);

void	debug_assets(t_txts txts);
void	print_map(char **map, void (*printer)(char c));
void	print_type(char c);
void	print_verification(char c);
void	debug(char *message);

void	reset_after_bfs(char **map);
bool	check_player_nb(char **map);
bool	check_map_content(char **map);

#endif