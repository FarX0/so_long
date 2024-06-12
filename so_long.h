/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:32:17 by tfalchi           #+#    #+#             */
/*   Updated: 2024/06/12 18:58:06 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "libft/get_next_line_bonus.h"
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "minilibx/mlx.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

typedef struct s_character
{
	void		*imgbase;
	int			with;
	int			height;
	int			x; // posizione player
	int			y; // posizione player
	int			countplayer;
}				t_character;

typedef struct s_image
{
	void		*img;
	int			with;
	int			height;
}				t_image;

typedef struct s_assets
{
	t_image		wall;
	t_image		exit;
	t_image		collectible;
	t_image		grass;
	t_character	character;
}				t_assets;

typedef struct s_map
{
	char		**matrix;
	int			ctrlmy;
	int			ctrlmx;
	int			is_map_valid;
	int			countcoll;
	int			countexit;
	int			reachcoll;
	int			reachexit;
}				t_map;

typedef struct s_data
{
	t_assets	img;
	void		*mlx;
	void		*mlx_win;
	t_map		map;
}				t_data;

void		map_implementation(char **argv);
char		**map_creation(char *filename);
void		*put_xmp(void *mlx, char *filename, int *width, int *height);
int			ft_key_hook(int keysym, t_data *data);
int			exit_program(void);
int			ft_closegame(t_data *data);
int			ft_move_player(t_data *data, int keysym);
char		*ft_strtrimfree(char *s1, char *set, int *trimmed);
int			ft_isinset(char c, char *set);
int			count_lines_fd(char *filename);
int			count_lines(char **matrix);
int			count_columns(char **matrix);
void		ft_print_matrix(char **matrix);
void		load_assets(t_data *data);
int			render_next_frame(t_data *data);
void		print_immage(t_data *data, int x, int y);
t_data		*try_reach(t_data *data, int x, int y, char **map);
void		countfind_map(t_data *data);
void		find_player(t_data *data);
void		try_move(t_data *data, int y, int x);
char		**dup_matrix(char **matrix, char *filename);
t_data		*initialize_data(t_data *data);
void		error_controll(t_data *data, char **argv);	
void		non_so_come_chiamarlo(t_data *data, int i, char **argv);
void		charater_tranform_collect(t_data *data, int i);
void		from_exit_to_grass(t_data *data, int i, int j);
int			from_grass_to_exit(t_data *data, int i);
int			matrix_creation(char ***matrix, char **line, int fd, int y);
void		free_matrix(char **matrix);

#endif
