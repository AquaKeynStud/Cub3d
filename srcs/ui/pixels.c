/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:32:30 by arocca            #+#    #+#             */
/*   Updated: 2025/10/17 14:19:19 by abouclie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	get_pixel(t_image *img, int x, int y)
{
	int	*pixels;

	pixels = (int *)img->addr;
	return (pixels[y * img->plen + x]);
}

void	put_pixel(t_image *img, int x, int y, int color)
{
	int	*pixels;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	pixels = (int *)img->addr;
	pixels[y * img->plen + x] = color;
}
