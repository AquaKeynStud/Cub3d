/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:06:13 by arocca            #+#    #+#             */
/*   Updated: 2025/10/08 15:20:29 by abouclie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

/* -- Includes -- */
# include "mlx.h"
# include "data.h"
# include "player.h"
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
	t_player	player;
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

/* -- Error Messages -- */
# define ERROR			"\t\e[107;1;31m     🏮 Error: "
# define ERRNOLOG		"\e[1;38;5;203m🈲    %s: %s    🈲\e[0m\n"
# define USAGE_ERR		"\e[1;31m😾 Usage: %s <path_to_map.cub> 😾\e[0m\n"

/* -- Info Messages -- */
# define INFO		"\t\e[107;1;34m     🗻 Info: "
# define TOPBAND	"\n\t\e[1;35m꧁  ⟣──╼━━━━ﾒ %s ﾒ━━━━╾──⟢ ꧂  \e[0m\n"
# define BOTTOMBAND	"\t\e[1;35m%s꧁  ⟣──╼━━━ﾒ %s - %s ﾒ━━━╾──⟢ ꧂  \e[0m\n\n"

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
void	print_map(char **map, void (*printer)(char c));

int	close_on_esc(int keycode, t_data *data);

#endif