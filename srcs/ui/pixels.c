/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:32:30 by arocca            #+#    #+#             */
/*   Updated: 2025/10/15 18:47:03 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->slen + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel(t_image *img, int x, int y)
{
	char	*pixel;

	pixel = img->addr + (y * img->slen + x * (img->bpp / 8));
	return (*(unsigned int *)pixel);
}
