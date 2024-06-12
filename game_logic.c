/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:57:50 by tfalchi           #+#    #+#             */
/*   Updated: 2024/06/12 13:53:40 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h" ///LEVA I PRINTF

int	ft_key_hook(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		ft_closegame(data);
	if (keysym == XK_w || keysym == XK_a || keysym == XK_s || keysym == XK_d)
		ft_move_player(data, keysym);
	return (0);
}

void	try_move(t_data *data, int y, int x)
{
	static int	i = 0;
	static int	j = 0;

	if (y < 0 || x < 0)
		return ;
	if (data->map.matrix[y][x] == '0' || data->map.matrix[y][x] == 'C'
		|| data->map.matrix[y][x] == 'E')
	{
		if (data->map.matrix[y][x] == 'C')
		{
			i++;
			charater_tranform_collect(data, i);
		}
		find_player(data);
		if (j == 1)
			from_exit_to_grass(data, i, j);
		else
			data->map.matrix[data->img.character.y][data->img.character.x] = 48;
		if (data->map.matrix[y][x] == 'E')
			j = from_grass_to_exit(data, i);
		data->map.matrix[y][x] = 'P';
		data->img.character.y = y;
		data->img.character.x = x;
	}
}

void	charater_tranform_collect(t_data *data, int i)
{
	if (i == 1)
		mlx_destroy_image(data->mlx, data->img.character.imgbase);
	if (i == 1)
		data->img.character.imgbase = put_xmp(data->mlx,
				"immage/1catcharacter.xpm", &data->img.character.with,
				&data->img.character.height);
	if (i == 2)
		mlx_destroy_image(data->mlx, data->img.character.imgbase);
	if (i == 2)
		data->img.character.imgbase = put_xmp(data->mlx,
				"immage/2catcharacter.xpm", &data->img.character.with,
				&data->img.character.height);
	else if (i == 3)
	{
		mlx_destroy_image(data->mlx, data->img.character.imgbase);
		data->img.character.imgbase = put_xmp(data->mlx,
				"immage/3catcharacter.xpm", &data->img.character.with,
				&data->img.character.height);
	}
	if (i == data->map.countcoll)
	{
		mlx_destroy_image(data->mlx, data->img.exit.img);
		data->img.exit.img = put_xmp(data->mlx, "immage/exit.xpm",
				&data->img.exit.with, &data->img.exit.height);
	}
}

void	from_exit_to_grass(t_data *data, int i, int j)
{
	mlx_destroy_image(data->mlx, data->img.character.imgbase);
	data->map.matrix[data->img.character.y][data->img.character.x] = 'E';
	j = 0;
	if (i == 0)
		data->img.character.imgbase = put_xmp(data->mlx,
				"immage/basic_character.xpm", &data->img.character.with,
				&data->img.character.height);
	else if (i == 1)
		data->img.character.imgbase = put_xmp(data->mlx,
				"immage/1catcharacter.xpm", &data->img.character.with,
				&data->img.character.height);
	else if (i == 2)
		data->img.character.imgbase = put_xmp(data->mlx,
				"immage/2catcharacter.xpm", &data->img.character.with,
				&data->img.character.height);
	else if (i >= 3)
		data->img.character.imgbase = put_xmp(data->mlx,
				"immage/3catcharacter.xpm", &data->img.character.with,
				&data->img.character.height);
}

int	from_grass_to_exit(t_data *data, int i)
{
	if (i == data->map.countcoll)
		ft_closegame(data);
	mlx_destroy_image(data->mlx, data->img.character.imgbase);
	if (i == 0)
		data->img.character.imgbase = put_xmp(data->mlx,
				"immage/basic_character_exit.xpm", &data->img.character.with,
				&data->img.character.height);
	else if (i == 1)
		data->img.character.imgbase = put_xmp(data->mlx,
				"immage/1character_exit.xpm", &data->img.character.with,
				&data->img.character.height);
	else if (i == 2)
		data->img.character.imgbase = put_xmp(data->mlx,
				"immage/2character_exit.xpm", &data->img.character.with,
				&data->img.character.height);
	else if (i >= 3)
		data->img.character.imgbase = put_xmp(data->mlx,
				"immage/3character_exit.xpm", &data->img.character.with,
				&data->img.character.height);
	return (1);
}
