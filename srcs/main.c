/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:32:04 by arocca            #+#    #+#             */
/*   Updated: 2025/10/08 08:41:50 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (data->assets.east.img)
		mlx_destroy_image(data->mlx, data->assets.east.img);
	if (data->assets.west.img)
		mlx_destroy_image(data->mlx, data->assets.west.img);
	if (data->assets.south.img)
		mlx_destroy_image(data->mlx, data->assets.south.img);
	if (data->assets.north.img)
		mlx_destroy_image(data->mlx, data->assets.north.img);
	if (data->map.map)
		double_free((void **)data->map.map, 0);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(code);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2 || !has_ext(argv[1], ".cub"))
		return (ft_printf(USAGE_ERR, argv[0]));
	print_header();
	ft_memset(&data, 0, sizeof(t_data));
	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	if (!get_info_from_file(&data, argv[1]))
		clean_exit(&data, EXIT_FAILURE);
	debug_assets(data.assets);
	if (!configure_map(&data.map))
		clean_exit(&data, EXIT_FAILURE);
	print_map(data.map.map, print_type);
	if (!create_window(&data, 800, 600, "cub3d"))
	{
		free(data.mlx);
		return (1);
	}
	mlx_hook(data.win, 17, 0, mlx_loop_end, data.mlx);
	mlx_hook(data.win, 2, 1L << 0, close_on_esc, &data);
	mlx_loop(data.mlx);
	mlx_destroy_window(data.mlx, data.win);
	clean_exit(&data, EXIT_SUCCESS);
	return (0);
}
