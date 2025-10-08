/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:06:13 by arocca            #+#    #+#             */
/*   Updated: 2025/10/08 08:42:23 by arocca           ###   ########.fr       */
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

# define EOL			"     \e[0m\n"

/* -- Error Reports Macros -- */
# define ERROR			"\t\e[107;1;31m     🏮 Error: "
# define ERRNOLOG		"\e[1;38;5;203m🈲    %s: %s    🈲\e[0m\n"
# define USAGE_ERR		"\e[1;31m😾 Usage: %s <path_to_map.cub> 😾\e[0m\n"

# define WALL_DATA_ERR	"🪾  Failed to initialize %s wall image 🍂"
# define COLOR_DATA_ERR	"🌈 No color found for %s 🍡"

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

/* -- Error Functions -- */
bool	err(char *msg);
bool	err_errno(char *msg);
bool	err_str(char *msg, char *str);

/* -- Print Functions -- */
void	print_type(char c);
void	debug(char *message);
void	print_verification(char c);
void	print_map(char **map, void (*printer)(char c));

int	close_on_esc(int keycode, t_data *data);

#endif