#include "solong.h"

void map_implementation(char **argv)
{
	t_data *data;
	char **mappa;
	int i = 0;

	data = NULL;
	data = initialize_data(data);
	if (data == NULL)
	{
		printf("Error\n");
		ft_closegame(data);
	}
	data->mlx = mlx_init();
	if (data->mlx == NULL)
	{
		printf("Error mlx\n");
		ft_closegame(data);
	}
	data->map.matrix = map_creation(argv[1]);
	if (data->map.matrix == NULL || data->map.matrix[0] == NULL)
	{
		printf("Error map\n");
        ft_closegame(data);
	}
	data->mlx_win = mlx_new_window(data->mlx, ((count_columns(data->map.matrix)) * 64), ((count_lines(data->map.matrix)) * 64), "Hello world!");
	data->img.character.with = 64;
	data->img.character.height = 64;
	load_assets(data);
	countfind_map(data);
	mappa = dup_matrix(data->map.matrix, argv[1]);
	data = try_reach(data, 0, 0, mappa);
	while(mappa[i] != NULL)
	{
		free(mappa[i]);
		i++;
	}
	free(mappa);
	data->map.is_map_valid = 1;
	printf("countcoll = %d, countexit = %d, reachcoll = %d, reachexit = %d\n", data->map.countcoll, data->map.countexit, data->map.reachcoll, data->map.reachexit);
	if (data->map.countcoll != data->map.reachcoll)
	{
		printf("Error count collect\n");
		ft_closegame(data);	
	}
	else if (data->map.countexit != 1)
	{
		printf("Error count exit\n");
		ft_closegame(data);
	}
	mlx_hook(data->mlx_win, 17, 1L << 17, ft_closegame, data);
	mlx_key_hook(data->mlx_win, ft_key_hook, data);
	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_loop(data->mlx);
	return;
}

void *put_xmp(void *mlx, char *filename, int *width, int *height)
{
	void *data;

	data = mlx_xpm_file_to_image(mlx, filename, width, height);
	if (!data)
		return (NULL);
	return (data);
}

char **map_creation(char *filename)
{
	char **matrix;
	int x = 0;
	int i = 0;
	int y = 0;
	int fd;

	matrix = malloc(sizeof(char *) * (count_lines_fd(filename) + 1));
	if (matrix == NULL)
		return (matrix);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (printf("fd non trovato\n"), NULL);
	char *line = NULL;
	line = ft_strtrimfree(get_next_line(fd), "\n", &y);
	x = ft_strlen(line);
	while (line)
	{
		matrix[i] = ft_strdup(line);
		free(line);
		line = ft_strtrimfree(get_next_line(fd), "\n", &y);
		if (line == NULL)
			break;
		if (x != (int)ft_strlen(line))
		{
			printf("mappa non consistente\n");
			matrix[i] = NULL;
			return (free(line), matrix);
		}

		if (line[x] != '\0')
		{
			printf("linea senza null, %d, %c -\n", x, line[x]);
			matrix[i] = NULL;
			return (free(line), matrix);
		}
		i++;
	}
	return (close(fd), matrix[i + 1] = NULL, matrix);
}

t_data *initialize_data(t_data *data)
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

char **dup_matrix(char **matrix, char *filename)
{
	int i = 0;
	char **new_matrix;
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
	//free(matrix);
	return (new_matrix);
}

void countfind_map(t_data *data)
{
	int y = 0;
	int x = 0;

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