/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:06:13 by arocca            #+#    #+#             */
/*   Updated: 2025/11/05 09:45:33 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

/* -- Includes -- */
# include "mlx.h"
# include "data.h"
# include "events.h"
# include "mlx_int.h"
# include <stdbool.h>

/* -- Structures -- */
typedef struct s_data
{
	t_image		bg;
	t_map		map;
	t_image		dsp;
	void		*mlx;
	void		*win;
	t_file		file;
	int			win_w;
	int			win_h;
	t_txts		assets;
	t_player	player;
	t_inputs	inputs;
}			t_data;

/* -- Bonus Detector -- */
# ifndef BONUS
#  define BONUS 0
# endif

/* -- Gameplay Modificators -- */
# define FOV				60.0f
# define MAX_STAMINA		300
# define SENSIBILITY		0.0003f
# define PLAYER_SPEED		0.025f
# define CROSSAIR_SIZE		4
# define CROSSAIR_COLOR		0xFFFFFF
# define ROTATION_SPEED		0.01f

/* -- Render Modificators -- */
# define MIN_RENDER			8.0f
# define MAX_RENDER			16.0f
# define BG_FADE_SPREAD		3.0f
# define FOG_COLOR			0xFFFFFF

/* -- Readible Variables -- */
# define PI				3.14159265358979323846
# define EOL			"     \e[0m\n"
# define CROSS			17
# define PRESS			2
# define RELEASE		3
# define MOUSE_MOV		6
# define LOOKUP_VAL		1024

/* -- Error Messages -- */
# define ERROR			"\n\t\e[107;1;31m     🏮 Error: "
# define ERRNOLOG		"\e[1;38;5;203m🈲    %s: %s    🈲\e[0m\n"
# define USAGE_ERR		"\e[1;31m😾 Usage: %s <path_to_map.cub> 😾\e[0m\n"

/* -- Info Messages -- */
# define INFO			"\t\e[107;1;34m     🗻 Info: "
# define TOPBAND		"\n\t\e[1;35m꧁  ⟣──╼━━━━ﾒ %s ﾒ━━━━╾──⟢ ꧂  \e[0m\n"
# define BOTTOMBAND		"\t\e[1;35m%s꧁  ⟣──╼━━━ﾒ %s - %s ﾒ━━━╾──⟢ ꧂  \e[0m\n\n"

/* -- Mini-map -- */
# define TILE_SIZE		30
# define WIDTH_SIZE		12
# define HEIGHT_SIZE	10
# define MAP_PADDING	15
# define BG_COLOR		0x0f0f0f
# define WALL_COLOR		0x6f6f6f
# define FLOOR_COLOR	0xffffff
# define PLR_COLOR		0x00FF00

/* -- Logs Functions -- */
void	print_header(void);

/* -- Display Functions -- */
bool	create_window(t_data *data, int width, int height, char *name);

/* -- Error Functions -- */
bool	err(char *msg);
bool	err_str(char *msg, char *str);
bool	err_errno(char *msg, char *custom_err, bool exit_err);

/* -- Print Functions -- */
void	print_type(char c);
void	print_verification(char c);
bool	info(char *message, char *format, char *str);
bool	player_infos(t_player player, char orientation);
void	print_map(char **map, t_player player, void (*printer)(char c));

void	raycast(t_data *data);
void	clean_exit(t_data *data, int code);

long	get_tick_time(void);

#endif