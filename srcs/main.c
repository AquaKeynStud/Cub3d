/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:32:04 by arocca            #+#    #+#             */
/*   Updated: 2025/09/18 17:47:45 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include <stdbool.h>
#include "ft_printf.h"

static bool	create_window(t_data *data, int width, int height, char *name)
{
	int	screen_width;
	int	screen_height;

	if (!width || !height)
		return (false);
	mlx_get_screen_size(data->mlx, &screen_width, &screen_height);
	if (width > screen_width || height > screen_height)
		return (false);
	if (width < 0)
		width = screen_width;
	if (height < 0)
		height = screen_height;
	data->win = mlx_new_window(data->mlx, width, height, name);
	if (!data->win)
		return (false);
	ft_printf("%s🗼 Window size : %ix%i 🚞", INFO, width, height);
	return (true);
}

static bool	has_ext(const char *filename, char *ext)
{
	int		len;
	int		pad;

	len = ft_strlen(filename);
	pad = ft_strlen(ext);
	if (len < pad || !*filename || !*ext)
		return (false);
	while (pad >= 0)
	{
		if (filename[len - pad] != ext[ft_strlen(ext) - pad])
			return (false);
		pad--;
	}
	return (true);
}

int main(int argc, char **argv)
{
	t_data	data;
	if (argc != 2 || !has_ext(argv[1], ".cub"))
		return (ft_printf("\e[1;31mUsage: %s <map file>\e[0m\n", argv[0]) - 30);	// A potentiellement changer
	print_header();
	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	if (!create_window(&data, 800, 600, "cub3d"))
	{
		free(data.mlx);
		return (1);
	}
	mlx_hook(data.win, 17, 0, mlx_loop_end, data.mlx);
	mlx_loop(data.mlx);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0);
}
