/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:06:59 by tfalchi           #+#    #+#             */
/*   Updated: 2024/06/12 18:30:16 by tfalchi          ###   ########.fr       */
/*                                                              yyyy              */
/* ************************************************************************** */

#include "so_long.h"

void	map_implementation(char **argv)
{
	t_data	*data;

	data = NULL;
	data = initialize_data(data);
	if (data == NULL)
	{
		ft_printf("Error\n");
		ft_closegame(data);
	}
	data->map.matrix = map_creation(argv[1]);
	error_controll(data, argv);
	mlx_hook(data->mlx_win, 17, 1L << 17, ft_closegame, data);
	mlx_key_hook(data->mlx_win, ft_key_hook, data);
	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_loop(data->mlx);
	return ;
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (*matrix == NULL)
		return ;
	while ((matrix)[i])
	{
		free((matrix)[i]);
		(matrix)[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}


void	error_controll(t_data *data, char **argv)
{
	int		i;

	i = 0;
	data->mlx = mlx_init();
	if (data->mlx == NULL)
	{
		ft_printf("Error mlx\n");
		ft_closegame(data);
	}
	if (data->map.matrix == NULL || data->map.matrix[0] == NULL)
	{
		ft_printf("Error map\n");
		ft_closegame(data);
	}
	data->mlx_win = mlx_new_window(data->mlx, ((count_columns(data->map.matrix))
				* 64), ((count_lines(data->map.matrix)) * 64), "Hello world!");
	data->img.character.with = 64;
	data->img.character.height = 64;
	load_assets(data);
	countfind_map(data);
	non_so_come_chiamarlo(data, i, argv);
}

void	non_so_come_chiamarlo(t_data *data, int i, char **argv)
{
	char	**mappa;

	mappa = dup_matrix(data->map.matrix, argv[1]);
	data = try_reach(data, 0, 0, mappa);
	while (mappa[i] != NULL)
	{
		free(mappa[i]);
		i++;
	}
	free(mappa);
	data->map.is_map_valid = 1;
	if (data->map.countcoll != data->map.reachcoll)
	{
		ft_printf("Error count collect\n");
		ft_closegame(data);
	}
	else if (data->map.countexit != 1)
	{
		ft_printf("Error count exit\n");
		ft_closegame(data);
	}
}

void	*put_xmp(void *mlx, char *filename, int *width, int *height)
{
	void	*data;

	data = mlx_xpm_file_to_image(mlx, filename, width, height);
	if (!data)
		return (NULL);
	return (data);
}
