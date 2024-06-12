/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:49:00 by tfalchi           #+#    #+#             */
/*   Updated: 2024/06/12 14:05:05 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	render_next_frame(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (data->map.matrix[y])
	{
		while (data->map.matrix[y][x])
		{
			print_immage(data, x, y);
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

void	print_immage(t_data *data, int x, int y)
{
	if (data->map.matrix[y][x] == '1')
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.wall.img, (x
				* 64), (y * 64));
	else if (data->map.matrix[y][x] == '0')
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.grass.img,
			(x * 64), (y * 64));
	else if (data->map.matrix[y][x] == 'P')
	{
		mlx_put_image_to_window(data->mlx, data->mlx_win,
			data->img.character.imgbase, (x * 64), (y * 64));
		data->img.character.x = x;
		data->img.character.y = y;
	}
	else if (data->map.matrix[y][x] == 'C')
		mlx_put_image_to_window(data->mlx, data->mlx_win,
			data->img.collectible.img, (x * 64), (y * 64));
	else if (data->map.matrix[y][x] == 'E')
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.exit.img, (x
				* 64), (y * 64));
	else
	{
		ft_printf("Error A data->map.matrix[y][x] = %c\n",
			data->map.matrix[y][x]);
		exit(1);
	}
}
