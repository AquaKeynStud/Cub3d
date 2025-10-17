/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:46:53 by arocca            #+#    #+#             */
/*   Updated: 2025/10/16 21:12:18 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	red(int color)
{
	return ((color >> 16) & 0xFF);
}

int	green(int color)
{
	return ((color >> 8) & 0xFF);
}

int	blue(int color)
{
	return (color & 0xFF);
}
