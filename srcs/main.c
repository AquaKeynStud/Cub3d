/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:32:04 by arocca            #+#    #+#             */
/*   Updated: 2025/11/01 11:40:07 by arocca           ###   ########.fr       */
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

static bool	setup_data(t_data *data, char *filename)
{
	ft_memset(data, 0, sizeof(t_data));
	(*data).mlx = mlx_init();
	if (!(*data).mlx)
		return (err("Failed to initialize mlx"));
	if (!get_info_from_file(data, filename))
		clean_exit(data, EXIT_FAILURE);
	debug_assets((*data).assets);
	if (!configure(data, &data->map))
		clean_exit(data, EXIT_FAILURE);
	return (true);
}

static bool	setup_display(t_data *data)
{
	if (!create_window(data, 1920, 1080, "cub3d"))
	{
		free(data->mlx);
		return (1);
	}
	data->player.sprint.start.x = data->win_w / 6;
	data->player.sprint.start.y = 8 * data->win_h / 9;
	data->player.sprint.len.x = data->win_w / 4;
	data->player.sprint.len.y = data->win_h / 30;
	if (!new_image(&data->dsp, data->mlx, data->win_w, data->win_h))
		return (err("Failed to create display render image"));
	if (!new_image(&data->bg, data->mlx, data->win_w, data->win_h))
		return (err("Failed to create background render image"));
	create_background(data, data->assets);
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
	setup_display(&data);
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
