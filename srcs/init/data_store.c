/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_store.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:10:37 by arocca            #+#    #+#             */
/*   Updated: 2025/10/08 10:25:12 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"

static int	to_rgb(char *s)
{
	int		r;
	int		g;
	int		b;
	char	**split;

	if (!s || !*s || count_char(s, ',') != 2)
		return (-1);
	split = ft_split(s, ',');
	if (!split || !*split)
		return (-1);
	if (!split[1] || !split[2] || split[3])
	{
		double_free((void **)split, 0);
		return (-1);
	}
	r = strict_pos_atoi(split[0]);
	g = strict_pos_atoi(split[1]);
	b = strict_pos_atoi(split[2]);
	double_free((void **)split, 0);
	if (r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0)
		return (-1);
	return (r << 16 | g << 8 | b);
}

static t_image	get_image(t_data *data, char *path, char *ext)
{
	t_image	img;

	(void)ext;
	if (!has_ext(path, ".xpm"))
	{
		err_errno(path, INVALID_EXT, false);
		return ((t_image){0});
	}
	img.img = mlx_xpm_file_to_image(data->mlx, path, &img.width, &img.height);
	if (!img.img)
	{
		err_errno(path, NULL, false);
		return ((t_image){0});
	}
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.slen, &img.endian);
	return (img);
}

static bool	upscale_map(char ***map, int *pos, int *cap)
{
	int		slot;
	char	**tmp;

	slot = sizeof(char *) * (*cap);
	if (!*map && *pos)
		return (false);
	if (!*map)
	{
		*map = (char **)malloc(slot);
		if (!*map)
			return (err(MAP_SIZE_ERR));
	}
	if ((*pos) >= (*cap) - 1)
	{
		tmp = (char **)ft_realloc(*map, slot, (slot * 2));
		if (!tmp)
		{
			double_free((void **)*map, 0);
			return (err(MAP_UPSC_ERR));
		}
		*map = tmp;
		(*cap) *= 2;
	}
	return (true);
}

bool	parse_param(t_data *data, char *line)
{
	char	*value;

	if (count_words(line, " \t\n\v\f\r") != 2)
		return (err_str(MANY_ARGS_ERR, line));
	value = get_word(line, 1);
	if (!ft_strncmp(line, "F ", 2) && data->assets.floor == -1)
		data->assets.floor = to_rgb(value);
	else if (!ft_strncmp(line, "C ", 2) && data->assets.ceiling == -1)
		data->assets.ceiling = to_rgb(value);
	else if (!ft_strncmp(line, "EA ", 3) && !data->assets.east.img)
		data->assets.east = get_image(data, value, ".xpm");
	else if (!ft_strncmp(line, "WE ", 3) && !data->assets.west.img)
		data->assets.west = get_image(data, value, ".xpm");
	else if (!ft_strncmp(line, "SO ", 3) && !data->assets.south.img)
		data->assets.south = get_image(data, value, ".xpm");
	else if (!ft_strncmp(line, "NO ", 3) && !data->assets.north.img)
		data->assets.north = get_image(data, value, ".xpm");
	else
	{
		free(value);
		return (err_str(INVALID_ARG, line));
	}
	free(line);
	free(value);
	return (true);
}

bool	parse_map(char ***map, char *line, int *pos, int *cap)
{
	int		slot;
	char	**tmp;

	slot = sizeof(char *);
	if (line && *line)
	{
		if (!upscale_map(map, pos, cap))
			return (false);
		(*map)[(*pos)] = line;
		(*map)[(*pos) + 1] = NULL;
		(*pos)++;
		return (true);
	}
	tmp = ft_realloc((*map), (*cap) * slot, (*pos + 1) * slot);
	if (!tmp)
	{
		double_free((void **)(*map), 0);
		return (err(MAP_CROP_ERR));
	}
	(*map) = tmp;
	return (true);
}
