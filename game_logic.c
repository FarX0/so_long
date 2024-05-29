#include "solong.h"

int ft_key_hook(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		ft_closegame(data);
	if (keysym == XK_w || keysym == XK_a || keysym == XK_s || keysym == XK_d)
		ft_move_player(data, keysym);
	return (0);
}

void	try_move(t_data *data, int y, int x)
{
	if (y < 0 || x < 0)
		return;
	if (data->map.matrix[y][x] == '0' || data->map.matrix[y][x] == 'C')
	{
		if (data->map.matrix[y][x] == 'C')
			// score increase;
		if (data->map.matrix[y][x] == 'e')
			// exit level;
		find_Player(data);
		data->map.matrix[data->img.character.y][data->img.character.x] = '0';
		data->map.matrix[y][x] = 'P';
		data->img.character.y = y;
		data->img.character.x = x;
	}
}

int ft_move_player(t_data *data, int keysym)
{
	int y = data->img.character.y;
	int x = data->img.character.x;

	//printf("y = %d, x = %d\n", y, x);
	//printf("keysym = %d\n", keysym);
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
	write(1, "\n", 1);
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

void find_Player(t_data *data)
{
	int y = 0;
	int x = 0;

	while(data->map.matrix[y])
	{
		while(data->map.matrix[y][x])
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