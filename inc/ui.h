/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:34:59 by arocca            #+#    #+#             */
/*   Updated: 2025/10/16 21:11:29 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

/* -- Includes -- */
# include "data.h"
# include "events.h"

/* -- Structures -- */
typedef struct s_txt_col
{
	int		end;
	int		start;
	float	y_step;
	float	txt_pos;
	int		line_len;
}			t_txt_col;

typedef struct s_data	t_data;

/* -- Draw Functions -- */
int		get_pixel(t_image *img, int x, int y);
void	display_background(t_data *data, t_txts txt);
void	display_wall(t_data *data, t_ray ray, int x);
void	put_pixel(t_image *img, int x, int y, int color);
int		distance_blur(double distance, int color, int bg);

/* -- Windows Handling Functions -- */
int		apply_fog(int color, double dist);
int		apply_fade(int color, double factor);
#endif