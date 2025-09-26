/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_logs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 22:05:31 by arocca            #+#    #+#             */
/*   Updated: 2025/09/25 15:04:17 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"

void    debug_assets(t_txts txts)
{
	ft_printf(TOPBAND, "🌆 Assets 🏗️ ");
    ft_printf("\t%7cNorth - %p, %dx%dp\n", ' ', txts.north.img,
			txts.north.width, txts.north.height);
	ft_printf("\t%7cSouth - %p, %dx%dp\n", ' ', txts.south.img,
			txts.south.width, txts.south.height);
	ft_printf("\t%7cEast - %p, %dx%dp\n", ' ', txts.east.img,
			txts.east.width, txts.east.height);
	ft_printf("\t%7cWest - %p, %dx%dp\n", ' ', txts.west.img,
			txts.west.width, txts.west.height);
	ft_printf("\t%7cFloor - R:%i, G:%i, B:%i\n", ' ',
		(txts.floor >> 16) & 0xFF, (txts.floor >> 8) & 0xFF, txts.floor & 0xFF);
	ft_printf("\t%7cCeiling - R:%i, G:%i, B:%i\n", ' ',
		(txts.ceiling >> 16) & 0xFF, (txts.ceiling >> 8) & 0xFF, txts.ceiling & 0xFF);
	ft_printf(BOTTOMBAND, "   ", "肌", "理");
}

static void	print_type(char c)
{
	if (c == ' ')
		ft_printf("   ");
	else if (in_str(c, "NSWE", false))
		ft_printf("🎐 ");
	else if (c == '1')
		ft_printf("🪵 ");
	else if (c == '0')
		ft_printf("🌱 ");
}

void	print_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		ft_printf("\t%4i ", i + 1);
		while (map[i][j])
			print_type(map[i][j++]);
		ft_printf("\n");
		i++;
	}
	j = 0;
	ft_printf("\t     ");
	while (map[0][j])
		ft_printf("%2i ", ++j);
	ft_printf("\n\n");
}
