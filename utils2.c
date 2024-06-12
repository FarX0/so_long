/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:47:06 by tfalchi           #+#    #+#             */
/*   Updated: 2024/06/12 18:07:56 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_move_player(t_data *data, int keysym)
{
	int	y;
	int	x;

	y = data->img.character.y;
	x = data->img.character.x;
	if (keysym == KEY_W)
		try_move(data, y - 1, x);
	if (keysym == KEY_A)
		try_move(data, y, x - 1);
	if (keysym == 115)
		try_move(data, y + 1, x);
	if (keysym == 100)
		try_move(data, y, x + 1);
	return (0);
}

void	ft_print_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		write(1, matrix[i], ft_strlen(matrix[i]));
		write(1, "\n", 1);
		i++;
	}
	write(1, "\n", 1);
}

int	ft_closegame(t_data *data)
{
	if (data->map.matrix != NULL)
		free_matrix(data->map.matrix);
	if (data->img.character.imgbase != NULL)
		mlx_destroy_image(data->mlx, data->img.character.imgbase);
	if (data->img.wall.img != NULL)
		mlx_destroy_image(data->mlx, data->img.wall.img);
	if (data->img.exit.img != NULL)
		mlx_destroy_image(data->mlx, data->img.exit.img);
	if (data->img.collectible.img != NULL)
		mlx_destroy_image(data->mlx, data->img.collectible.img);
	if (data->img.grass.img != NULL)
		mlx_destroy_image(data->mlx, data->img.grass.img);
	if (data->mlx_win != NULL)
		mlx_destroy_window(data->mlx, data->mlx_win);
	if (data->mlx != NULL)
		mlx_destroy_display(data->mlx);
	return (free(data->mlx), free(data), exit(1), 0);
}

static char	*ft_result(char *s1, size_t start, size_t end, int *trimmed)
{
	char	*dst;
	size_t	i;

	i = 0;
	if (!s1[start])
	{
		free(s1);
		return (NULL);
	}
	dst = ft_calloc((end - start + 2), sizeof(char));
	if (dst == NULL)
		return (free(s1), free(dst), NULL);
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

char	*ft_strtrimfree(char *s1, char *set, int *trimmed)
{
	size_t	start;
	size_t	end;

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
