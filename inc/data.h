/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:54:57 by arocca            #+#    #+#             */
/*   Updated: 2025/11/03 07:42:07 by abouclie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

/* -- Includes -- */
# include "my_math.h"

/* -- Structures -- */
typedef struct s_file
{
	int		fd;
	int		nl;
	int		pos;
	int		cap;
	int		line_nb;
	int		has_door;
}			t_file;

typedef struct s_image
{
	int		bpp;
	int		slen;
	int		plen;
	void	*img;
	int		*addr;
	int		width;
	int		endian;
	int		height;
}			t_image;

typedef struct s_door
{
	t_idot			pos;
	bool			open;
	long			tick;
	int				status;
	t_image			texture;

	struct s_door	*next;
}			t_door;

typedef struct s_txts
{
	t_image	west;
	t_image	east;
	t_image	north;
	t_image	south;

	t_image	door;

	int		floor;
	int		ceiling;

	t_door	*doors;
	t_image	d_anim[5];

	double	*fog;
	double	*alpha;
	double	fog_unit;
	double	alpha_unit;
}			t_txts;

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
}			t_map;

typedef struct s_sprint
{
	t_idot	len;
	t_idot	start;
}			t_sprint;

typedef struct s_player
{
	double		x;
	double		y;
	t_dot		ori;
	t_dot		cam;
	double		angle;
	double		cam_fov;

	t_sprint	sprint;
	int			stamina;
	int			sprint_mult;
}			t_player;

typedef struct	s_square
{
	int	start_y;
	int	start_x;
	int	tile_y;
	int	tile_x;
	int	color;
}				t_square;

typedef struct s_minimap
{
	int			center_y;
	int			center_x;
	int			ori_y;
	int			ori_x;
	t_dot		frac;
	t_square	square;
}				t_minimap;

typedef struct s_data	t_data;

/* -- Read Info Messages -- */
# define MAPLOG		"\t\e[107;1;38;5;210m     "
# define READ_END	"🎏 Data saved successfully, file closed 📚"
# define READ_START	"⛩️  Start reading file: %s 🚏"

/* -- Syntax Error Messages -- */
# define INVALID_EXT	"Invalid extension"
# define INVALID_ARG	"🧫 Invalid identifier: `%.2s` 🦠"
# define INVALID_LINE	"🏞️  Invalid line in file : `%s` 🍥"
# define EMPTY_CONFIG	"🌁 Config file seems empty... 🔬"
# define MANY_ARGS_ERR	"🧨 Too many arguments on line: `%s` 🧯"

/* -- Map Error Messages -- */
# define EMPTY_LINE		"🌁 Empty line in map 📜"
# define NO_MAP_ERR		"🧭 No map found in file 🗺️ "
# define MAP_NOT_EOF	"🚧 No parameters allowed after the map 🌄"
# define MAP_CROP_ERR	"💉 Failed to crop the map at the right size 🧪"
# define MAP_SIZE_ERR	"🏚️  Failed to allocate memory for the map ⛓️"
# define MAP_UPSC_ERR	"☣️  Failed to upscale the map; aborting... 📐"

/* -- Assets Error Messages -- */
# define WALL_DATA_ERR	"🪾  Failed to initialize %s wall image 🍂"
# define COLOR_DATA_ERR	"🌈 No color found for %s 🍡"

/* -- File Functions -- */
bool	parse_param(t_data *data, char *line);
bool	has_ext(const char *filename, char *ext);
bool	get_info_from_file(t_data *data, const char *filename);
bool	parse_map(char ***map, char *line, int *pos, int *cap);

bool	init_fog_table(t_txts *txts);
bool	init_alpha_table(t_txts *txts);
double	get_fog(double *fogs, double dist, double unit);
double	get_alpha(double *alpha, double dist, double unit);

/* -- Doors Functions -- */
t_door	*get_door(t_door *doors, int y, int x);
bool	door_open(t_door *doors, int y, int x);
bool	free_all_doors(t_data *data, t_door **doors);
bool	add_door(t_data *data, t_door **doors, int y, int x);
bool	init_doors(t_data *data, t_door **doors, char **map);

/* -- Mlx Complement -- */
t_image	get_image(t_data *data, char *path, char *ext);
void	copy_image(t_data *data, t_image *dest, t_image *src);
bool	new_image(t_image *image, void *mlx, int width, int height);

#endif