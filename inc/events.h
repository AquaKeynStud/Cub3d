/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:03:18 by arocca            #+#    #+#             */
/*   Updated: 2025/11/05 11:29:02 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

/* -- Includes -- */
# include "my_math.h"

/* -- Structures -- */
typedef struct s_inputs
{
	bool	esc;
	bool	alt;
	bool	left;
	bool	right;
	bool	forward;
	bool	backward;
	bool	left_shift;
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
	bool	door;
	double	origin;

	t_dot	cell;
	t_dot	step;

	t_dot	dir;
	t_dot	magn;
	t_dot	delta;
}			t_ray;

typedef struct s_data	t_data;

/* -- Inputs -- */
# define KEY_W			122 // 119
# define KEY_A			113 // 97
# define KEY_S			115
# define KEY_D			100
# define KEY_E			101
# define KEY_ESC		65307
# define KEY_LALT		65513
# define KEY_LEFT		65361
# define KEY_RIGHT		65363
# define KEY_LSHIFT		65505

/* -- Inputs Messages -- */
# define MOUSE_ON	"✅ Mouse is now enabled ❇️"
# define MOUSE_OFF	"⛔️ Mouse is now disabled 💢"

# define NO_KEY_ERR	"%s🈲 The key : %c isn't handled 🈲%s"

/* -- Inputs Functions -- */
int			key_pressed(int keycode, t_data *data);
int			key_released(int keycode, t_data *data);

/* -- Movement Functions -- */
int			mouse_move(int x, int y, t_data *data);
void		rotate_player(t_data *data, double angle);
void		handle_movement(t_data *data, t_player *player);
void		update_velocity(t_inputs *inputs, t_player *player, bool active);

/* -- Loop Functions -- */
void		raycast(t_data *data);
int			end_loop(t_data *data);
int			game_loop(t_data *data);

/* -- Utils Functions -- */
int			red(int color);
int			blue(int color);
int			green(int color);

/* -- Mini-map -- */
t_minimap	init_map(t_data *data);
void		draw_map(t_data *data);
void		init_square(t_data *data, t_minimap *map, int x, int y);
void		draw_player_triangle(t_data *data, t_minimap *map, int size);

#endif