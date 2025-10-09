/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:22:45 by arocca            #+#    #+#             */
/*   Updated: 2025/10/09 19:29:44 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	game_loop(t_data *data)
{
	if (data->inputs.forward)
		return (0); // Faire avancer le joueur
	if (data->inputs.backward)
		return (0); // Faire reculer le joueur
	if (data->inputs.rotate_left)
		return (0); // Rotation à gauche
	if (data->inputs.rotate_right)
		return (0); // Rotation à droite
	return (0);
}