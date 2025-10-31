/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:32:04 by arocca            #+#    #+#             */
/*   Updated: 2025/10/31 10:28:14 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "cub.h"
#include "libft.h"
#include "config.h"
#include "ft_printf.h"

bool	has_ext(const char *filename, char *ext)
{
	int	len;
	int	pad;

	pad = ft_strlen(ext);
	len = ft_strlen(filename);
	if (len < pad || !*filename || !*ext)
		return (false);
	return (ft_strncmp(filename + (len - pad), ext, pad) == 0);
}

void	clean_exit(t_data *data, int code)
{
	int	i = 0;
	if (data->assets.east.img)
		mlx_destroy_image(data->mlx, data->assets.east.img);
	if (data->assets.west.img)
		mlx_destroy_image(data->mlx, data->assets.west.img);
	if (data->assets.south.img)
		mlx_destroy_image(data->mlx, data->assets.south.img);
	if (data->assets.north.img)
		mlx_destroy_image(data->mlx, data->assets.north.img);
	if (data->assets.door.img)
		mlx_destroy_image(data->mlx, data->assets.door.img);
	if (data->file.has_door)
	{
		while (i < 5)
			mlx_destroy_image(data->mlx, data->assets.d_anim[i++].img);
	}
	if (data->dsp.img)
		mlx_destroy_image(data->mlx, data->dsp.img);
	if (data->bg.img)
		mlx_destroy_image(data->mlx, data->bg.img);
	if (data->map.map)
		double_free((void **)data->map.map, 0);
	if (data->assets.fog)
		free(data->assets.fog);
	if (data->assets.alpha)
		free(data->assets.alpha);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(code);
}

bool	setup_door(t_data *data, t_file *file)
{
	int	x;
	int	y;
	int	count;

	if (!file->has_door || file->has_door > DOOR_LIMIT - 1)
		return (file->has_door == false);
	y = 0;
	count = 0;
	while (data->map.map[y])
	{
		x = 0;
		while (data->map.map[y][x])
		{
			if (data->map.map[y][x] == 'D')
			{
				data->doors[count].pos.x = x;
				data->doors[count].pos.y = y;
				data->doors[count++].open = false;
			}
			x++;
		}
		y++;
	}
	return (true);
}

static bool	setup_data(t_data *data, char *filename)
{
	ft_memset(data, 0, sizeof(t_data));
	(*data).mlx = mlx_init();
	if (!(*data).mlx)
		return (err("Failed to initialize mlx"));
	if (!get_info_from_file(data, filename))
		clean_exit(data, EXIT_FAILURE);
	if (!setup_door(data, &data->file))
		return (err("Failed to get doors data"));
	debug_assets((*data).assets);
	if (!configure(data, &data->map))
		clean_exit(data, EXIT_FAILURE);
	return (true);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2 || !has_ext(argv[1], ".cub"))
		return (ft_printf(USAGE_ERR, argv[0]));
	print_header();
	if (!setup_data(&data, argv[1]))
		return (1);
	if (!init_fog_table(&data.assets) || !init_alpha_table(&data.assets))
		return (1);
	if (!create_window(&data, 480, 200, "cub3d"))
	{
		free(data.mlx);
		return (1);
	}
	data.player.sprint.start.x = data.win_w / 6;
	data.player.sprint.start.y = 8 * data.win_h / 9;
	data.player.sprint.len.x = data.win_w / 4;
	data.player.sprint.len.y = data.win_h / 30;
	init_display_images(&data);
	mlx_hook(data.win, CROSS, 0, end_loop, &data);
	mlx_hook(data.win, PRESS, 1L << 0, key_pressed, &data);
	mlx_hook(data.win, RELEASE, 1L << 1, key_released, &data);
	mlx_hook(data.win, MOUSE_MOV, 1L << 6, mouse_move, &data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
	mlx_destroy_window(data.mlx, data.win);
	clean_exit(&data, EXIT_SUCCESS);
	return (0);
}
