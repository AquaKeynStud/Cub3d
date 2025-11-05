/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:59:47 by arocca            #+#    #+#             */
/*   Updated: 2025/11/05 12:20:53 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include <fcntl.h>

static bool	get_data_from_line(t_data *data, t_file *file, char *line)
{
	bool	empty;

	empty = is_empty_line(line);
	if (in_str(*line, "NSWEFCD", false))
	{
		if (!data->map.map)
			return (parse_param(data, line));
		return (err(MAP_NOT_EOF));
	}
	if (in_str(*line, "10 ", false))
	{
		if (data->file.nl)
			return (err(EMPTY_LINE));
		if (BONUS && in_str('D', line, false))
			file->has_door += 1;
		return (parse_map(&data->map.map, line, &file->pos, &file->cap));
	}
	if (empty)
	{
		free(line);
		return (data->file.nl += (data->file.nl == false));
	}
	else
		data->file.nl -= (data->file.nl == true);
	return (err_str(INVALID_LINE, line));
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
		else if (!get_data_from_line(data, &data->file, line))
			break ;
	}
	if (line)
		free(line);
	get_next_line(-1);
	return (false);
}

static bool	everything_set(t_data *data, t_txts txts)
{
	if (!BONUS && data->file.has_door)
		return (err(DOOR_MAP_ERR));
	if (!txts.east.img || !txts.east.addr)
		return (err_str(WALL_DATA_ERR, "east"));
	if (!txts.west.img || !txts.west.addr)
		return (err_str(WALL_DATA_ERR, "west"));
	if (!txts.north.img || !txts.north.addr)
		return (err_str(WALL_DATA_ERR, "north"));
	if (!txts.south.img || !txts.south.addr)
		return (err_str(WALL_DATA_ERR, "south"));
	if (data->file.has_door && (!txts.door.img || !txts.door.addr))
		return (err_str(WALL_DATA_ERR, "door"));
	if (txts.floor == -1)
		return (err_str(COLOR_DATA_ERR, "floor"));
	if (txts.ceiling == -1)
		return (err_str(COLOR_DATA_ERR, "ceiling"));
	if (!data->map.map || !*data->map.map)
		return (err(NO_MAP_ERR));
	return (true);
}

bool	get_door_anims_img(t_data *data, t_txts *assets)
{
	assets->d_anim[0] = get_image(data, "./assets/door_break_1.xpm", ".xpm");
	assets->d_anim[1] = get_image(data, "./assets/door_break_2.xpm", ".xpm");
	assets->d_anim[2] = get_image(data, "./assets/door_break_3.xpm", ".xpm");
	assets->d_anim[3] = get_image(data, "./assets/door_break_4.xpm", ".xpm");
	assets->d_anim[4] = get_image(data, "./assets/door_break_5.xpm", ".xpm");
	return (assets->d_anim[0].addr
		&& assets->d_anim[1].addr
		&& assets->d_anim[2].addr
		&& assets->d_anim[3].addr
		&& assets->d_anim[4].addr);
}

bool	get_info_from_file(t_data *data, const char *filename)
{
	bool	checker;
	t_txts	*assets;

	assets = &data->assets;
	data->file.cap = 16;
	assets->floor = -1;
	assets->ceiling = -1;
	data->file.fd = open(filename, O_RDONLY);
	if (data->file.fd == -1)
	{
		err_errno((char *)filename, NULL, true);
		return (false);
	}
	info(READ_START, MAPLOG, (char *)filename);
	checker = read_lines(data);
	close(data->file.fd);
	if (!data->file.line_nb)
		return (err(EMPTY_CONFIG));
	if (data->file.has_door && !get_door_anims_img(data, assets))
		return (err(DOOR_ANIMS_ERR));
	if (checker && everything_set(data, *assets))
		return (info(READ_END, MAPLOG, NULL));
	return (false);
}
