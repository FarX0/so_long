/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:56:59 by tfalchi           #+#    #+#             */
/*   Updated: 2024/06/12 18:30:07 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**map_creation(char *filename)
{
	char	**matrix;
	int		y;
	int		fd;
	char	*line;

	y = 0;
	line = NULL;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_printf("fd non trovato\n"), NULL);
	matrix = ft_calloc((count_lines_fd(filename) + 1), sizeof(char *));
	if (matrix == NULL)
		return (matrix);
	line = ft_strtrimfree(get_next_line(fd), "\n", &y);
	matrix_creation(&matrix, &line, fd, y);
	if (matrix == NULL)
		ft_printf("Error matrix\n");
	return (close(fd), matrix);
}

int	matrix_creation(char ***matrix, char **line, int fd, int y)
{
	int	x;
	int	i;

	i = 0;
	x = ft_strlen(*line);
	while (*line)
	{
		(*matrix)[i] = ft_strdup(*line);
		free(*line);
		*line = ft_strtrimfree(get_next_line(fd), "\n", &y);
		if (*line == NULL)
			break ;
		if (x != (int)ft_strlen(*line))
		{
			ft_printf("mappa non consistente\n");
			return (free_matrix(*matrix), free(line), 1);
		}
		if ((*line)[x] != '\0')
		{
			ft_printf("linea senza null, %d, %c -\n", x, (*line)[x]);
			return (free_matrix(*matrix), free(line), 1);
		}
		i++;
	}
	return (free(*line), 1);
}

t_data	*initialize_data(t_data *data)
{
	data = malloc(sizeof(t_data));
	data->img.wall.img = NULL;
	data->img.exit.img = NULL;
	data->img.collectible.img = NULL;
	data->img.grass.img = NULL;
	data->img.character.imgbase = NULL;
	data->img.character.with = 0;
	data->img.character.height = 0;
	data->img.character.x = 0;
	data->img.character.y = 0;
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->map.matrix = NULL;
	data->map.ctrlmy = 0;
	data->map.ctrlmx = 0;
	data->map.is_map_valid = 0;
	data->map.countcoll = 0;
	data->map.countexit = 0;
	data->map.reachcoll = 0;
	data->map.reachexit = 0;
	return (data);
}

char	**dup_matrix(char **matrix, char *filename)
{
	int		i;
	char	**new_matrix;

	i = 0;
	new_matrix = malloc(sizeof(char *) * (count_lines_fd(filename) + 1));
	while (matrix[i])
	{
		new_matrix[i] = ft_strdup(matrix[i]);
		i++;
	}
	while (i != 0 && matrix[i])
	{
		free(matrix[i]);
		i--;
	}
	new_matrix[i] = NULL;
	return (new_matrix);
}

void	countfind_map(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (data->map.matrix[y])
	{
		while (data->map.matrix[y][x])
		{
			if (data->map.matrix[y][x] == 'C')
				data->map.countcoll++;
			if (data->map.matrix[y][x] == 'E')
				data->map.countexit++;
			x++;
		}
		x = 0;
		y++;
	}
}
