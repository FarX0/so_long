/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:59:48 by tfalchi           #+#    #+#             */
/*   Updated: 2024/05/24 13:16:04 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

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
void ft_print_matrix(char **matrix);
void load_assets(t_data *data);
int render_next_frame(t_data *data);
void print_immage(t_data *data, int x, int y);

int main(void)
{
	map_implementation();
	return (0);
}

void    try_reach(t_data *data)
{
	data->map.exitcount = 0;
	data->map.collcount = 0;
	if (data->map.ctrlmy == NULL && data->map.ctrlmx == NULL)
	{
		data->map.ctrlmx = data->img.character.x;
		data->map.ctrlmy = data->img.character.y;
	}
    if (data->map.matrix[data->map.ctrlmx][data->map.ctrlmy] == 'E')
        data->map.exitcount = data->map.exitcount + 1;
    if (data->map.matrix[data->map.ctrlmx][data->map.ctrlmy] == 'C')
        data->map.collcount = data->map.collcount + 1;
    if (data->map.matrix[data->map.ctrlmx][data->map.ctrlmy] == '1' || data->map.matrix[data->map.ctrlmx][data->map.ctrlmy] == '9')
        return ;
    data->map.matrix[data->map.ctrlmx][data->map.ctrlmy] = '9';
    data->map.ctrlmx = data->map.ctrlmx + 1;
    try_reach(data);
    data->map.ctrlmy = data->map.ctrlmy + 1;
    try_reach(data);
    data->map.ctrlmx = data->map.ctrlmx - 1;
    try_reach(data);
    data->map.ctrlmy = data->map.ctrlmy -1;
    try_reach(data);
    return ;
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

void load_assets(t_data *data)
{
	data->img.wall.img = put_xmp(data->mlx, "immage/wall.xpm", &data->img.wall.with, &data->img.wall.height);
	data->img.exit.img = put_xmp(data->mlx, "immage/exit.xpm", &data->img.exit.with, &data->img.exit.height);
	data->img.collectible.img = put_xmp(data->mlx, "immage/collectible.xpm", &data->img.collectible.with, &data->img.collectible.height);
	data->img.grass.img = put_xmp(data->mlx, "immage/grass.xpm", &data->img.grass.with, &data->img.grass.height);
	data->img.character.img1 = put_xmp(data->mlx, "immage/1catcharacter.xpm", &data->img.character.with, &data->img.character.height);
	data->img.character.img2 = put_xmp(data->mlx, "immage/2catcharacter.xpm", &data->img.character.with, &data->img.character.height);
	data->img.character.img3 = put_xmp(data->mlx, "immage/3catcharacter.xpm", &data->img.character.with, &data->img.character.height);
	data->img.character.imgbase = put_xmp(data->mlx, "immage/basic_character.xpm", &data->img.character.with, &data->img.character.height);
}
int render_next_frame(t_data *data)
{
	int y = 0;
	int x = 0;
	
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

void print_immage(t_data *data, int x, int y)
{
	if (data->map.matrix[y][x] == '1')
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.wall.img, (x * 64), (y * 64));
	else if (data->map.matrix[y][x] == '0')
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.grass.img, (x * 64), (y * 64));
	else if (data->map.matrix[y][x] == 'P')
	{
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.character.imgbase, (x * 64), (y * 64));
		data->img.character.x = x;
		data->img.character.y = y;
	}
	else if (data->map.matrix[y][x] == '2')
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.character.img1, (x * 64), (y * 64));
	else if (data->map.matrix[y][x] == '3')
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.character.img2, (x * 64), (y * 64));
	else if (data->map.matrix[y][x] == '4')
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.character.img3, (x * 64), (y * 64));
	else
	{
		printf("Error\n");
		exit(1);
	}
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
	char **matrix;
	int x = 0;
	int i = 0;
	int y = 0;
	int fd;

	matrix = malloc(sizeof(t_data));
	fd = open("maps/map1", O_RDONLY);
	if (fd == -1)
	{
		printf("A\n");
		return (NULL);
	}

	char *line = NULL;
	matrix = malloc(sizeof(char *) * (count_lines("maps/map1") + 1));
	line = ft_strtrimfree(get_next_line(fd), "\n", &y);
	x = ft_strlen(line);
	while (line)
	{
		matrix[i] = ft_strdup(line);
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

	matrix[i] = NULL;
	close(fd);
	return (matrix);
}

void map_implementation()
{
	t_data data;  /////puntatore da provare.......................................................
	data.img.character.with = 64;
	data.img.character.height = 64;
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, 1920, 1080, "Hello world!");
	data.map.matrix = malloc(sizeof(t_data));
	data.map.matrix = map_creation();
	if (data.map.matrix == NULL)
	{
		printf("Error\n");
		exit(1);
	}

	try_reach(&data);
    data.map.is_map_valid = 1;
    if (data.map.collcount != collectibles)
        {
		printf("Error\n");
		exit(1);
	}
    else if (data.map.exitcount != 1)
        {
		printf("Error\n");
		exit(1);
	}
	load_assets(&data);
	mlx_loop_hook(data.mlx, render_next_frame, &data);
	mlx_hook(data.mlx_win, 17, 1L << 17, ft_closegame, &data);
	mlx_key_hook(data.mlx_win, ft_key_hook, &data);
	mlx_loop(data.mlx);
	return;
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
	int y = data->img.character.y;
	int x = data->img.character.x;

	printf("y = %d, x = %d\n", y, x);
	printf("keysym = %d\n", keysym);
	if (keysym == 119)
	{
		if (y < 0 || x < 0)
			return (0);
		printf("w");
		if (data->map.matrix[y - 1][x] == '0')
		{
			data->map.matrix[y][x] = '0';
			data->map.matrix[y - 1][x] = 'P';
		}
	}
	if (keysym == 97)
	{
		if (y < 0 || x < 0)
			return (0);
		printf("a");
		if (data->map.matrix[y][x - 1] == '0')
		{
			data->map.matrix[y][x] = '0';
			data->map.matrix[y][x - 1] = 'P';
		}
	}
	if (keysym == 115)
	{
		if (y < 0 || x < 0)
			return (0);
		printf("s");
		if (data->map.matrix[y + 1][x] == '0')
		{
			data->map.matrix[y][x] = '0';
			data->map.matrix[y + 1][x] = 'P';
		}
	}
	if (keysym == 100)
	{
		if (y < 0 || x < 0)
			return (0);
		printf("d");
		if (data->map.matrix[y][x + 1] && data->map.matrix[y][x + 1] == '0')
		{
			data->map.matrix[y][x] = '0';
			data->map.matrix[y][x + 1] = 'P';
		}
	}

	return (0);
}
void ft_print_matrix(char **matrix)
{
	int i;
	i = 0;
	while (matrix[i])
	{
		write(1, matrix[i], ft_strlen(matrix[i]));
		write(1, "\n", 1);
		i++;
	}
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
