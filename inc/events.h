/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:03:18 by arocca            #+#    #+#             */
/*   Updated: 2025/10/23 11:54:08 by abouclie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

/* -- Includes -- */
# include <stdbool.h>

/* -- Structures -- */
typedef struct s_inputs
{
	bool	esc;
	bool	alt;
	bool	left;
	bool	right;
	bool	forward;
	bool	backward;
	bool	rotate_left;
	bool	rotate_right;

	int		mouse_x;
	bool	allow_mouse;
}			t_inputs;

typedef struct s_raycast
{
	bool	hit;
	double	pos;
	int		side;
	double	dist;
	double	origin;

	t_dot	cell;
	t_dot	step;

	t_dot	dir;
	t_dot	magn;
	t_dot	delta;
}			t_ray;

typedef struct s_data	t_data;

/* -- Inputs -- */
# define KEY_W			119 // 122
# define KEY_A			97 // 113
# define KEY_S			115
# define KEY_D			100
# define KEY_ESC		65307
# define KEY_LEFT		65361
# define KEY_RIGHT		65363

/* -- Error Messages -- */
# define NO_KEY_ERR	"%s🈲 The key : %c isn't handled 🈲%s"

/* -- Inputs Functions -- */
int		key_pressed(int keycode, t_data *data);
int		key_released(int keycode, t_data *data);

/* -- Movement Functions -- */
void	handle_movement(t_data *data);
int		mouse_move(int x, int y, t_data *data);

/* -- Loop Functions -- */
int		game_loop(t_data *data);

/* -- Utils Functions -- */
int		red(int color);
int		blue(int color);
int		green(int color);

void		draw_map(t_data *data);
void		init_square(t_data *data, t_minimap *map, int x, int y);
t_minimap	init_map(t_data *data);
void		draw_player_triangle(t_data *data, t_minimap *map, int size);
void		clear_image(t_image *img, int color);
void		get_ray_result(t_data *data, t_ray *ray);


#endif