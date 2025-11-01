/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tables.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:29:11 by arocca            #+#    #+#             */
/*   Updated: 2025/11/01 12:18:02 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"

double	get_fog(double *fogs, double dist, double unit)
{
	int	index;

	if (!BONUS)
		return (1.0);
	if (dist >= MIN_RENDER)
		return (0.0);
	index = (int)(dist * unit);
	if (index < 0)
		index = 0;
	else if (index >= LOOKUP_VAL)
		index = LOOKUP_VAL - 1;
	return (fogs[index]);
}

double	get_alpha(double *alpha, double dist, double unit)
{
	int	index;

	if (dist < MIN_RENDER)
		return (0.0);
	if (dist > MAX_RENDER || !BONUS)
		return (1.0);
	index = (int)((dist - MIN_RENDER) * unit);
	if (index < 0)
		index = 0;
	else if (index >= LOOKUP_VAL)
		index = LOOKUP_VAL - 1;
	return (alpha[index]);
}

bool	init_alpha_table(t_txts *txts)
{
	int		i;
	double	step;
	double	dist;
	double	inv_rend;

	i = 0;
	inv_rend = 1.0 / (MAX_RENDER - MIN_RENDER);
	step = (MAX_RENDER - MIN_RENDER) / LOOKUP_VAL;
	txts->alpha_unit = LOOKUP_VAL / (MAX_RENDER - MIN_RENDER);
	txts->alpha = (double *)ft_calloc(LOOKUP_VAL, sizeof(double));
	if (!txts->alpha)
		return (false);
	while (i < LOOKUP_VAL)
	{
		dist = MIN_RENDER + i * step;
		txts->alpha[i++] = clamp((dist - MIN_RENDER) * inv_rend, 0, 1);
	}
	return (true);
}

bool	init_fog_table(t_txts *txts)
{
	int		i;
	double	step;
	double	dist;
	double	inv_rend;

	i = 0;
	inv_rend = 1.0 / MIN_RENDER;
	step = MIN_RENDER / LOOKUP_VAL;
	txts->fog_unit = LOOKUP_VAL / MIN_RENDER;
	txts->fog = (double *)calloc(LOOKUP_VAL, sizeof(double));
	if (!txts->fog)
		return (false);
	while (i < LOOKUP_VAL)
	{
		dist = i * step;
		txts->fog[i++] = clamp(1.0 - (dist * inv_rend), 0, 1);
	}
	return (true);
}
