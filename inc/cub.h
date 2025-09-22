/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:06:13 by arocca            #+#    #+#             */
/*   Updated: 2025/09/22 15:27:13 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

/* -- Includes -- */
# include "map.h"
# include "mlx.h"
# include <stdbool.h>
# include "mlx_int.h"

/* -- Structures -- */
typedef struct	s_data
{
	void	*mlx;
	void	*win;
	t_map	map;
	t_txts	assets;
}			t_data;

/* -- Macros -- */
# define KEY_W 122 // 119
# define KEY_A 113 // 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

# define EOL		"     \e[0m\n"	
# define INFO		"\t\e[107m     \e[1;34m🗻 Info: "
# define ERROR		"\t\e[100m     \e[1;34m🏮 Error: "
# define MAP_REP	"\t\e[107m     \e[1;38;5;210m"

# define USAGE_ERR "\e[1;31m😾 Usage: %s <path_to_map.cub> 😾\e[0m\n"

# define IMG_EXT ".xpm"

/* -- Logs Functions -- */
void	print_header(void);

/* -- File Functions -- */
bool	has_ext(const char *filename, char *ext);

bool	get_info_from_file(t_data *data, const char *filename);

bool	err(char *msg);


void    debug_assets(t_data *data);
void	debug(char *message, char *str);

#endif