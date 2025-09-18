/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:17:53 by arocca            #+#    #+#             */
/*   Updated: 2025/09/18 17:54:27 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include <fcntl.h>
#include <stdbool.h>

bool	get_images(t_data *data)
{
	char	*line;
	char	**splitted;
	
	while (1)
	{
		line = get_next_line(data->map->fd);
		if (!line)
			break ;
		else if (!*line || is_empty_line(line))
			continue ;
		else
		{
			ft_split_str(line, " \t")
		}
	}
}

bool	get_info_from_file(t_data *data, const char *filename)
{
	data->map->fd = open(filename, O_RDONLY);
	if (data->map->fd <= 0)
		return (false);
	
	close(data->map->fd);
	return (true);
}