/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:03:18 by arocca            #+#    #+#             */
/*   Updated: 2025/10/10 15:00:53 by arocca           ###   ########.fr       */
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
	bool	left;
	bool	right;
	bool	forward;
	bool	backward;
	bool	rotate_left;
	bool	rotate_right;
}			t_inputs;

typedef struct s_data	t_data;

/* -- Inputs -- */
# define KEY_W			122 // 119
# define KEY_A			113 // 97
# define KEY_S			115
# define KEY_D			100
# define KEY_ESC		65307
# define KEY_LEFT		65361
# define KEY_RIGHT		65363

/* -- Error Messages -- */
# define NO_KEY_ERR	"%s🈲 The key : %c isn't handled 🈲%s"

/* -- Inputs Functions -- */
int	key_pressed(int keycode, t_data *data);
int	key_released(int keycode, t_data *data);

/* -- Loop Functions -- */
int	game_loop(t_data *data);

#endif