/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:59:47 by arocca            #+#    #+#             */
/*   Updated: 2025/09/26 21:23:19 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include <fcntl.h>

static bool	get_data_from_line(t_data *data, char *line, int *pos, int *cap)
{
	if (is_empty_line(line) && data->map.map)
		return (err("Empty line in map"));
	if (in_str('\t', line, false))
		return (err("Tabs are not allowed in map"));
	if (in_str(*line, "NSWEFC", false) && !data->map.map)
		return (parse_param(data, line));
	if (in_str(*line, "10 ", false))
		return (parse_map(&data->map.map, line, pos, cap));
	return (err_str("Invalid line in file : `%s`", line));
}

static bool	read_lines(t_data *data)
{
	char	*line;
	int		position;
	int		capacity;

	position = 0;
	capacity = 16;
	while (1)
	{
		line = get_next_line(data->fd);
		if (!line)
			return (true);
		else if (!*line || (is_empty_line(line) && !data->map.map))
		{
			free(line);
			continue ;
		}
		else if (!get_data_from_line(data, line, &position, &capacity))
			break ;
	}
	if (line)
		free(line);
	get_next_line(-1);
	return (false);
}

static bool	everything_set(t_data *data, t_txts txts)
{
	if (!txts.east.img || !txts.east.addr)
		return (err_str(WALL_IMG_ERR, "east"));
	if (!txts.west.img || !txts.west.addr)
		return (err_str(WALL_IMG_ERR, "west"));
	if (!txts.north.img || !txts.north.addr)
		return (err_str(WALL_IMG_ERR, "north"));
	if (!txts.south.img || !txts.south.addr)
		return (err_str(WALL_IMG_ERR, "south"));
	if (!data->map.map || !*data->map.map)
		return (err("Erreur while reading the map"));
	return (true);
}

bool	get_info_from_file(t_data *data, const char *filename)
{
	bool	checker;

	data->fd = open(filename, O_RDONLY);
	if (data->fd == -1)
	{
		perror("open");
		return (false);
	}
	ft_printf("%s⛩️  Start reading file: %s 🚏%s", MAPLOG, filename, EOL);
	checker = read_lines(data);
	close(data->fd);
	if (checker && everything_set(data, data->assets))
		return (ft_printf("%s🎏 Read successfull, file closed 📚%s", MAPLOG, EOL));
	return (false);
}
