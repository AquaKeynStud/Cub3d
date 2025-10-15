/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:28:23 by arocca            #+#    #+#             */
/*   Updated: 2025/10/15 14:31:48 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MATH_H
# define MY_MATH_H

/* -- Includes -- */
# include <stdbool.h>

/* -- Structures -- */
typedef struct s_dot
{
	double	x;
	double	y;
}			t_dot;

/* -- Macros -- */
# define RAD(deg)		((deg) * (PI / 180))
# define DEG(rad)		((rad) * (180 / PI))
# define ABS(value)		((value) * (1 - 2 * ((value) < 0)))

/* -- Functions -- */
double	rad(double deg);
double	deg(double rad);
double	norm(double angle);
bool	in_bound(int x, int y, int width, int height);

#endif