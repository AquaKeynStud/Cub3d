/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:34:59 by arocca            #+#    #+#             */
/*   Updated: 2025/10/15 10:40:52 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

/* -- Includes -- */
#include "data.h"
#include "events.h"

/* -- Structures -- */
typedef struct s_data	t_data;

/* -- Draw Functions -- */
void	get_wall(t_data *data, t_ray ray, int x);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);

/* -- Windows Handling Functions -- */

#endif