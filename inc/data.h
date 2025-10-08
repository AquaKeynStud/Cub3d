/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:54:57 by arocca            #+#    #+#             */
/*   Updated: 2025/10/08 11:14:57 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

/* -- Includes -- */
# include <stdbool.h>

/* -- Structures -- */
typedef struct s_file
{
	int	fd;
	int	nl;
	int	pos;
	int	cap;
	int	line_nb;
}			t_file;

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

typedef struct s_data t_data;

/* -- Read Info Messages -- */
# define MAPLOG		"\t\e[107;1;38;5;210m     "
# define READ_END	"%s🎏 Data saved successfully, file closed 📚%s"
# define READ_START	"%s⛩️  Start reading file: %s 🚏%s"

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

#endif