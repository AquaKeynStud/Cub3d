/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:59:47 by arocca            #+#    #+#             */
/*   Updated: 2025/10/07 18:12:42 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include <fcntl.h>

static bool	get_data_from_line(t_data *data, char *line)
{
	bool	empty;

	empty = is_empty_line(line);
	if (in_str(*line, "NSWEFC", false))
	{
		if (!data->map.map)
			return (parse_param(data, line));
		return (err("The map should be after all parameters"));
	}
	if (in_str(*line, "10 ", false))
	{
		if (data->file.nl)
			return (err("Empty line in map"));
		return (parse_map(&data->map.map, line, &data->file.pos, &data->file.cap));
	}
	free(line);
	if (empty)
		return (data->file.nl += (data->file.nl == false));
	else
		return ((data->file.nl -= (data->file.nl == true)) || true);
	return (err_str("🏞️  Invalid line in file : `%s` 🍥", line));
}

static bool	read_lines(t_data *data)
{
	char	*line;

	while (1)
	{
		line = get_next_line(data->file.fd);
		if (!line)
		{
			get_next_line(-1);
			return (true);
		}
		data->file.line_nb++;
		if (!*line || (is_empty_line(line) && !data->map.map))
		{
			free(line);
			continue ;
		}
		else if (!get_data_from_line(data, line))
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
		return (err_str(WALL_DATA_ERR, "east"));
	if (!txts.west.img || !txts.west.addr)
		return (err_str(WALL_DATA_ERR, "west"));
	if (!txts.north.img || !txts.north.addr)
		return (err_str(WALL_DATA_ERR, "north"));
	if (!txts.south.img || !txts.south.addr)
		return (err_str(WALL_DATA_ERR, "south"));
	if (txts.floor == -1)
		return (err_str(COLOR_DATA_ERR, "floor"));
	if (txts.ceiling == -1)
		return (err_str(COLOR_DATA_ERR, "ceiling"));
	if (!data->map.map || !*data->map.map)
		return (err("🧭 No map found in file 🗺️"));
	return (true);
}

bool	get_info_from_file(t_data *data, const char *filename)
{
	bool	checker;

	data->file.cap = 16;
	data->assets.floor = -1;
	data->assets.ceiling = -1;
	data->file.fd = open(filename, O_RDONLY);
	if (data->file.fd == -1)
	{
		perror("open");
		return (false);
	}
	ft_printf("%s⛩️  Start reading file: %s 🚏%s", MAPLOG, filename, EOL);
	checker = read_lines(data);
	close(data->file.fd);
	if (!data->file.line_nb)
		return (err("🌁 Config file seems empty... 🔬"));
	if (checker && everything_set(data, data->assets))
		return (ft_printf("%s🎏 Info saved, file closed 📚%s", MAPLOG, EOL));
	return (false);
}
