/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:06:13 by arocca            #+#    #+#             */
/*   Updated: 2025/10/13 19:24:28 by arocca           ###   ########.fr       */
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
	t_map		map;
	void		*mlx;
	void		*win;
	t_file		file;
	t_txts		assets;
	t_image		screen;
	t_player	player;
	t_inputs	inputs;
	int			screen_width;
	int			screen_height;
}			t_data;

/* -- Gameplay Modificators -- */
# define PLAYER_SPEED	0.005f
# define ROTATION_SPEED	0.005f
# define FOV			60.0
# define RENDER_DIST	100.0

/* -- Readible Variables -- */
# define EOL			"     \e[0m\n"
# define CROSS			17
# define PRESS			2
# define RELEASE		3
# define PI				3.14159265358979323846

/* -- Math Macros -- */
# define RAD(deg)		((deg) * (PI / 180))
# define DEG(rad)		((rad) * (180 / PI))
# define ABS(value)		((value) * (1 - 2 * ((value) < 0)))

/* -- Error Messages -- */
# define ERROR			"\n\t\e[107;1;31m     🏮 Error: "
# define ERRNOLOG		"\e[1;38;5;203m🈲    %s: %s    🈲\e[0m\n"
# define USAGE_ERR		"\e[1;31m😾 Usage: %s <path_to_map.cub> 😾\e[0m\n"

/* -- Info Messages -- */
# define INFO			"\t\e[107;1;34m     🗻 Info: "
# define TOPBAND		"\n\t\e[1;35m꧁  ⟣──╼━━━━ﾒ %s ﾒ━━━━╾──⟢ ꧂  \e[0m\n"
# define BOTTOMBAND		"\t\e[1;35m%s꧁  ⟣──╼━━━ﾒ %s - %s ﾒ━━━╾──⟢ ꧂  \e[0m\n\n"

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
void	debug(char *message);
void	print_verification(char c);
bool	info(char *message, char *format, char *str);
bool	player_infos(t_player player, char orientation);
void	print_map(char **map, t_player player, void (*printer)(char c));

/* -- Math functions -- */
double	rad(double deg);
double	deg(double rad);
double	norm(double angle);
bool	in_bound(int x, int y, int width, int height);

void	raycast(t_data *data);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
void	clean_exit(t_data *data, int code);

#endif