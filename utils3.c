/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:47:06 by tfalchi           #+#    #+#             */
/*   Updated: 2024/06/12 13:51:39 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_isinset(char c, char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

void	find_player(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (data->map.matrix[y])
	{
		while (data->map.matrix[y][x])
		{
			if (data->map.matrix[y][x] == 'P')
			{
				data->img.character.x = x;
				data->img.character.y = y;
			}
			x++;
		}
		x = 0;
		y++;
	}
}
