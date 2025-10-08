/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:21:06 by abouclie          #+#    #+#             */
/*   Updated: 2025/10/08 16:17:06 by abouclie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

typedef struct s_player
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	speed;
}				t_player;

void	draw_square(t_data *data, int x, int y, int size, int color);
void	draw_map(t_data *data);

void	move_forward(t_data *data);
void	move_back(t_data *data);
void	move_right(t_data *data);
void	move_left(t_data *data);

#endif