/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:17:53 by arocca            #+#    #+#             */
/*   Updated: 2025/09/22 15:28:11 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include <fcntl.h>

int	to_rgb(char *s)
{
	int		r;
	int		g;
	int		b;
	char	**split;

	if (!s || !*s)
		return (-1);
	split = ft_split(s, ',');
	free(s);
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
	if (r > 255 || g > 255 || b > 255)
		return (-1);
	return (r << 16 | g << 8 | b);
}

t_image	get_image(t_data *data, char *path, char *ext)
{
	t_image	img;

	debug("Entrée dans la fonction de récupération d'image: %s\n", path);
	(void)ext;
	if (!has_ext(path, ".xpm"))
	{
		debug("Mauvaise extension, sortie de la fonction...\n", NULL);
		return ((t_image){0});
	}
	debug("Le fichier à la bonne extension\n", NULL);
	img.img = mlx_xpm_file_to_image(data->mlx, path, &img.width, &img.height);
	if (!img.img)
	{
		debug("On a pas réussi à récupérer l'image\n", NULL);
		return ((t_image){0});
	}
	debug("On a réussi à trouver l'image\n", NULL);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.slen, &img.endian);
	return (img);
}

bool	parse_params(t_data *data, char *line)
{
	char	*value;

	debug("Entée ici: %s\n", line);
	if (count_words(line, " \t") != 2)
		return (err("Too many arguments on line"));
	value = get_word(line, 1);
	if (!ft_strncmp(line, "F ", 2))
		data->assets.floor = to_rgb(value);
	else if (!ft_strncmp(line, "C ", 2))
		data->assets.ceiling = to_rgb(value);
	else if (!ft_strncmp(line, "EA ", 3))
		data->assets.east = get_image(data, value, ".xpm");
	else if (!ft_strncmp(line, "WE ", 3))
		data->assets.west = get_image(data, value, ".xpm");
	else if (!ft_strncmp(line, "SO ", 3))
		data->assets.south = get_image(data, value, ".xpm");
	else if (!ft_strncmp(line, "NO ", 3))
		data->assets.north = get_image(data, value, ".xpm");
	else
	{
		free(value);
		return (err("Invalid line in file"));
	}
	free(value);
	return (true);
}

bool	parse_map(t_data *data)
{
	(void)data;
	return (true);
}

bool	read_lines(t_data *data)
{
	char	*line;

	while (1)
	{
		line = get_next_line(data->map.fd);
		if (!line)
			return (true);
		else if (!*line || is_empty_line(line))
		{
			free(line);
			debug("Ligne vide; on continue\n", NULL);
			continue ;
		}
		else if (in_str(*line, "NSWEFC", false) && !parse_params(data, line))
			break ;
		else if (!in_str(*line, " 01", false) && !parse_map(data))
			break ;
		else
			break ;
		free(line);
	}
	if (line)
		free(line);
	return (false);
}

bool	get_info_from_file(t_data *data, const char *filename)
{
	data->map.fd = open(filename, O_RDONLY);
	if (data->map.fd == -1)
	{
		perror("open");
		return (false);
	}
	ft_printf("%s⛩️  Start reading file: %s 🚏%s", MAP_REP, filename, EOL);
	read_lines(data);
	close(data->map.fd);
	ft_printf("%s⛩️  Read successfull, file closed 🚏%s", MAP_REP, EOL);
	return (true);
}
