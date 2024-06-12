/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:59:11 by tfalchi           #+#    #+#             */
/*   Updated: 2024/06/12 17:41:04 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_data	*try_reach(t_data *data, int y, int x, char **map)
{
	static int	i;

	if (i == 0)
	{
		find_player(data);
		x = data->img.character.x;
		y = data->img.character.y;
		i++;
	}
	if (map[y][x] == 'E')
		data->map.reachexit = data->map.reachexit + 1;
	if (map[y][x] == 'C')
		data->map.reachcoll = data->map.reachcoll + 1;
	if (map[y][x] == '1' || map[y][x] == '9')
		return (data);
	map[y][x] = '9';
	data = try_reach(data, y + 1, x, map);
	data = try_reach(data, y, x + 1, map);
	data = try_reach(data, y - 1, x, map);
	data = try_reach(data, y, x - 1, map);
	return (data);
}

int	count_lines_fd(char *filename)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
	return (count);
}

int	count_lines(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

int	count_columns(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[0][i])
		i++;
	return (i);
}

void	load_assets(t_data *data)
{
	data->img.wall.img = put_xmp(data->mlx, "immage/wall.xpm",
			&data->img.wall.with, &data->img.wall.height);
	data->img.exit.img = put_xmp(data->mlx, "immage/exitclosed.xpm",
			&data->img.exit.with, &data->img.exit.height);
	data->img.collectible.img = put_xmp(data->mlx, "immage/cat.xpm",
			&data->img.collectible.with, &data->img.collectible.height);
	data->img.grass.img = put_xmp(data->mlx, "immage/grass.xpm",
			&data->img.grass.with, &data->img.grass.height);
	data->img.character.imgbase = put_xmp(data->mlx,
			"immage/basic_character.xpm", &data->img.character.with,
			&data->img.character.height);
}
