/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:28:23 by arocca            #+#    #+#             */
/*   Updated: 2025/11/05 11:29:29 by arocca           ###   ########.fr       */
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

typedef struct s_idot
{
	int	x;
	int	y;
}			t_idot;

/* -- Functions -- */
double	rad(double deg);
double	deg(double rad);
long	get_tick_time(void);
double	clamp(double x, int min, int max);
bool	in_bound(int x, int y, int width, int height);

#endif