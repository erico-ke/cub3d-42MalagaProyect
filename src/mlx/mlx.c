/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:27:57 by erico-ke          #+#    #+#             */
/*   Updated: 2026/05/06 16:59:42 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	setup_image(t_data *data)
{
	data->img = mlx_new_image(data->mlx, SCREEN_W, SCREEN_H);
	if (!data->img)
	{
		perror("Error creating image");
		mlx_close_window(data->mlx);
		cleanup_data(data);
		exit(EXIT_FAILURE);
	}
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

static void	setup_game(t_data *data)
{
	load_textures(data);
	calculate_map_dimensions(data);
	init_player(data);
	mlx_loop_hook(data->mlx, game_loop, data);
	mlx_loop(data->mlx);
}

void	init_mlx(t_data *data)
{
	ft_printf("Attempting to initialize MLX...\n");
	data->mlx = mlx_init(SCREEN_W, SCREEN_H, "Cub3D", false);
	if (!data->mlx)
	{
		ft_printf("MLX initialization failed!\n");
		perror("Error initializing MLX");
		cleanup_data(data);
		exit(EXIT_FAILURE);
	}
	ft_printf("MLX initialized successfully!\n");
	mlx_key_hook(data->mlx, &handle_keypress, data);
	setup_image(data);
	setup_game(data);
}
