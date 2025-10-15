/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:34:59 by arocca            #+#    #+#             */
/*   Updated: 2025/10/15 18:48:05 by arocca           ###   ########.fr       */
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
	double	y_step;
	double	txt_pos;
	int		line_len;
}			t_txt_col;

typedef struct s_data	t_data;

/* -- Draw Functions -- */
void	display_background(t_data *data);
int		get_pixel(t_image *img, int x, int y);
void	display_wall(t_data *data, t_ray ray, int x);
void	put_pixel(t_image *img, int x, int y, int color);

/* -- Windows Handling Functions -- */

#endif