/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:34:59 by arocca            #+#    #+#             */
/*   Updated: 2025/10/22 15:54:02 by arocca           ###   ########.fr       */
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
	int		x;
	float	fog;
	int		end;
	int		start;
	float	alpha;
	int		wall_h;
	double	y_step;
	double	txt_pos;
}			t_txt_col;

typedef struct s_data	t_data;

/* -- Draw Functions -- */
int		get_pixel(t_image *img, int x, int y);
void	create_background(t_data *data, t_txts txt);
void	display_wall(t_data *data, t_ray ray, int x);
void	put_pixel(t_image *img, int x, int y, int color);

bool	init_display_images(t_data *data);
int		end_loop(t_data *data);

void	display_sprint(t_data *data, t_sprint s);

/* -- Windows Handling Functions -- */
int		apply_fog(int color, float factor);
int		apply_fade(int color, double factor);
int		distance_blur(int color, int bg, float alpha);
#endif