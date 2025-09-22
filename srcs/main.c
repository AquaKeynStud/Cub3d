/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:32:04 by arocca            #+#    #+#             */
/*   Updated: 2025/09/22 12:45:30 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include "ft_printf.h"

bool	err(char *msg)
{
	ft_printf(ERROR);
	ft_printf("%s", msg);
	ft_printf(EOL);
	return (false);
}

static bool	create_window(t_data *data, int width, int height, char *name)
{
	int	screen_width;
	int	screen_height;

	if (!width || !height)
		return (false);
	screen_width = 0;
	screen_height = 0;	
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
	ft_printf("%s🗼 Window size : %ix%i 🚞%s", INFO, width, height, EOL);
	return (true);	
}

bool has_ext(const char *filename, char *ext)
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
	if (data->assets.east.img)	// penser à un cleanup_assets...
		mlx_destroy_image(data->mlx, data->assets.east.img);
	if (data->assets.west.img)
		mlx_destroy_image(data->mlx, data->assets.west.img);
	if (data->assets.south.img)
		mlx_destroy_image(data->mlx, data->assets.south.img);
	if (data->assets.north.img)
		mlx_destroy_image(data->mlx, data->assets.north.img);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(code);
}

int close_on_esc(int keycode, t_data *data)
{
    if (keycode == 65307) // Échap sous Linux
        mlx_loop_end(data->mlx);
    return (0);
}

int main(int argc, char **argv)
{
	t_data	data;
	if (argc != 2 || !has_ext(argv[1], ".cub"))
		return (ft_printf(USAGE_ERR, argv[0]));
	print_header();
	ft_memset(&data, 0, sizeof(t_data));
	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	get_info_from_file(&data, argv[1]);
	debug_assets(&data);
	if (!create_window(&data, 800, 600, "cub3d"))
	{
		free(data.mlx);
		return (1);
	}
	mlx_hook(data.win, 17, 0, mlx_loop_end, data.mlx);
	mlx_hook(data.win, 2, 1L<<0, close_on_esc, &data);
	mlx_loop(data.mlx);
	mlx_destroy_window(data.mlx, data.win);
	clean_exit(&data, 0);
	return (0);
}
