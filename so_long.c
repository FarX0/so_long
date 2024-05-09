/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:59:48 by tfalchi           #+#    #+#             */
/*   Updated: 2024/05/09 10:58:20 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx/mlx.h"
#include "solong.h"
#include "libft/libft.h"
#include "libft/get_next_line_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void map_implementation();
char **map_creation();
void *put_xmp(void *mlx, char *filename, int *width, int *height);
int exit_program();

int main(void)
{
	map_implementation();
	
	return (0);
}

void *put_xmp(void *mlx, char *filename, int *width, int *height)
{
	void *data;

	data = mlx_xpm_file_to_image(mlx, filename, width, height);
	if (!data)
		return (NULL);
	return (data);
}

char **map_creation()
{
	t_data mappa;
	int i = 0;
	int fd;

	mappa.matrix = malloc(sizeof(t_data));
	fd = open("maps/map1", O_RDONLY);
	if (fd == -1)
	{
		return (NULL);
	}
	
	char *line = get_next_line(fd);
	mappa.matrix = malloc(sizeof(char *) * 5);
	while (line)
	{
		mappa.matrix[i] = ft_strdup(line);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	mappa.matrix[i] = NULL;
	close(fd);
	return (mappa.matrix);
}

void map_implementation()
{
	void *mlx;
	void *mlx_win;
	t_data mappa;
	t_data data;
	
	int i = 0;
	int x = 0;
	data.img.character.with = 64;
	data.img.character.height = 64;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mappa.matrix = malloc(sizeof(t_data));
	mappa.matrix = map_creation();
	if (mappa.matrix == NULL)
	{
		printf("Error\n");
		exit(1);
	}
	while (mappa.matrix[i])
	{
		printf("%s", mappa.matrix[i]);//stampa la mappa
		while (mappa.matrix[i][x])
		{
			if (mappa.matrix[i][x] == '1')
			{
				data.img.character.img = put_xmp(mlx, "immage/wall.xpm", &data.img.character.with, &data.img.character.height);
				mlx_put_image_to_window(mlx, mlx_win, data.img.character.img, (i * 64), (x * 64));
			}
			else if (mappa.matrix[i][x] == '0')
			{
				data.img.character.img = put_xmp(mlx, "immage/grass.xpm", &data.img.character.with, &data.img.character.height);
				mlx_put_image_to_window(mlx, mlx_win, data.img.character.img, (i * 64), (x * 64));
			}
			else if (mappa.matrix[i][x] == 'P')
			{
				data.img.character.img = put_xmp(mlx, "immage/1catcharacter.xpm", &data.img.character.with, &data.img.character.height);
				mlx_put_image_to_window(mlx, mlx_win, data.img.character.img, (i * 64), (x * 64));
			}
			x++;
		}
		x = 0;
		i++;
	}
	mlx_hook(mlx_win, 17, 1L << 17, exit_program, &data);
	mlx_loop(mlx);
}
int exit_program()
{
    exit(0);
    return (0);
}
