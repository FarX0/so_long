/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:59:48 by tfalchi           #+#    #+#             */
/*   Updated: 2024/05/14 12:08:41 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx/mlx.h"
#include "solong.h"
#include "libft/libft.h"
#include "libft/get_next_line_bonus.h"
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void map_implementation();
char **map_creation();
void *put_xmp(void *mlx, char *filename, int *width, int *height);
int ft_key_hook(int keysym, t_data *data);
int exit_program();
int ft_closegame(t_data *data);
int ft_move_player();
char *ft_strtrimfree(char *s1, char *set, int *trimmed);
int ft_isinset(char c, char *set);
static char *ft_result(char *s1, size_t start, size_t end, int *trimmed);
int count_lines(char *filename);

int main(void)
{
	map_implementation();
	return (0);
}

int count_lines(char *filename)
{
	int fd;
	int count;

	count = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (get_next_line(fd) != NULL)
		count++;
	return (count);
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
	int x = 0;
	int i = 0;
	int y = 0;
	int fd;

	mappa.matrix = malloc(sizeof(t_data));
	fd = open("maps/map1", O_RDONLY);
	if (fd == -1)
	{
		printf("A\n");
		return (NULL);
	}

	char *line = NULL;
	mappa.matrix = malloc(sizeof(char *) * (count_lines("maps/map1")));
	line = ft_strtrimfree(get_next_line(fd), "\n", &y);
	x = ft_strlen(line);
	while (line)
	{
		mappa.matrix[i] = ft_strdup(line);
		printf("line  %s -\n", line);
		i++;
		free(line);
		line = ft_strtrimfree(get_next_line(fd), "\n", &y);
		if (line == NULL)
			break;
		if (x != (int)ft_strlen(line))
		{
			free(line);
			printf("B\n");
			return (NULL);
		}

		if (line[x] != '\0')
		{
			free(line);
			printf("C, %d, %c -\n", x, line[x]);
			return (NULL);
		}
	}

	mappa.matrix[i] = NULL;
	close(fd);
	return (mappa.matrix);
}

void map_implementation()
{
	void *mlx;
	void *mlx_win;
	t_data data;

	int y = 0;
	int x = 0;
	data.img.character.with = 64;
	data.img.character.height = 64;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	data.matrix = malloc(sizeof(t_data));
	data.matrix = map_creation();
	if (data.matrix == NULL)
	{
		printf("Error\n");
		exit(1);
	}
	while (data.matrix[y])
	{
		while (data.matrix[y][x])
		{
			if (data.matrix[y][x] == '1')
			{
				data.img.character.img = put_xmp(mlx, "immage/wall.xpm", &data.img.character.with, &data.img.character.height);
				mlx_put_image_to_window(mlx, mlx_win, data.img.character.img, (x * 64), (y * 64));
			}
			else if (data.matrix[y][x] == '0')
			{
				data.img.character.img = put_xmp(mlx, "immage/grass.xpm", &data.img.character.with, &data.img.character.height);
				mlx_put_image_to_window(mlx, mlx_win, data.img.character.img, (x * 64), (y * 64));
			}
			else if (data.matrix[y][x] == 'P')
			{
				data.img.character.x = x;
				data.img.character.y = y;
				data.img.character.img = put_xmp(mlx, "immage/1catcharacter.xpm", &data.img.character.with, &data.img.character.height);
				mlx_put_image_to_window(mlx, mlx_win, data.img.character.img, (x * 64), (y * 64));
			}
			else
			{
				printf("Error\n");
				exit(1);
			}
			x++;
		}
		x = 0;
		y++;
	}
	mlx_hook(mlx_win, 17, 1L << 17, ft_closegame, &data);
	mlx_key_hook(mlx_win, ft_key_hook, &data);
	mlx_loop(mlx);
}
int ft_key_hook(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		ft_closegame(data);
	if (keysym == XK_w || keysym == XK_a || keysym == XK_s || keysym == XK_d)
		ft_move_player(data, keysym);
	return (0);
}

int ft_move_player(t_data *data, int keysym)
{
	int i = data->img.character.y;
	int x = data->img.character.x;

	if (data->matrix[i][x] == 'P')
	{
		if (keysym == XK_w)
		{
			printf("w");
			if (data->matrix[i - 1][x] == '0')
			{
				data->matrix[i][x] = '0';
				data->matrix[i - 1][x] = 'P';
			}
		}
		if (keysym == XK_a)
		{
			printf("a");
			if (data->matrix[i][x - 1] == '0')
			{
				data->matrix[i][x] = '0';
				data->matrix[i][x - 1] = 'P';
			}
		}
		if (keysym == XK_s)
		{
			printf("s");
			if (data->matrix[i + 1][x] == '0')
			{
				data->matrix[i][x] = '0';
				data->matrix[i + 1][x] = 'P';
			}
		}
		if (keysym == XK_d)
		{
			printf("d");
			if (data->matrix[i][x + 1] == '0')
			{
				data->matrix[i][x] = '0';
				data->matrix[i][x + 1] = 'P';
			}
		}
	}
	return (0);
}

int ft_closegame(t_data *data)
{
	exit(0);
	free(data);
	return (0);
}

static char *ft_result(char *s1, size_t start, size_t end, int *trimmed)
{
	char *dst;
	size_t i;

	i = 0;
	if (!s1[start])
	{
		free(s1);
		return (NULL);
	}
	dst = ft_calloc((end - start + 2), sizeof(char));
	if (dst == NULL)
		return (NULL);
	while (start <= end)
	{
		dst[i] = s1[start];
		start++;
		i++;
	}
	if (trimmed)
		*trimmed += ft_strlen(s1) - ft_strlen(dst);
	free(s1);
	if (ft_strlen(dst) == 0)
		return (free(dst), NULL);
	return (dst);
}

char *ft_strtrimfree(char *s1, char *set, int *trimmed)
{
	size_t start;
	size_t end;

	start = 0;
	end = 0;
	if (!s1)
		return (NULL);
	if (s1[0] == '\0')
		return (ft_result(s1, 0, 0, trimmed));
	while (s1[start] && ft_isinset(s1[start], set) == 1)
		start++;
	while (s1[end])
		end++;
	if (start == end)
		return (ft_result(s1, start, end, trimmed));
	end--;
	while (ft_isinset(s1[end], set) == 1)
		end--;
	return (ft_result(s1, start, end, trimmed));
}

int ft_isinset(char c, char *set)
{
	size_t i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}
