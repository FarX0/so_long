/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:32:17 by tfalchi           #+#    #+#             */
/*   Updated: 2024/05/28 14:56:11 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"
# include "libft/get_next_line_bonus.h"
# include <X11/keysym.h>

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

typedef struct	s_character {
	void	*img1;
	void	*img2;
	void	*img3;
	void	*imgbase;
	int		with;
	int		height;
	int		x; //posizione player
	int		y; //posizione player
}				t_character;

typedef struct	s_image {
	void	*img;
	int		with;
	int		height;
}				t_image;

typedef struct s_assets {
	t_image		wall;
	t_image		exit;
	t_image		collectible;
	t_image		grass;
	t_character	character;
}				t_assets;

typedef struct	s_map {
	char		**matrix;
	int			ctrlmy;
	int			ctrlmx;
	int			is_map_valid;
	int			countcoll;
	int			countexit;
	int 		reachcoll;
	int			reachexit;
}				t_map;

typedef struct	s_data {
	t_assets	img;
	void		*mlx;
	void 		*mlx_win;
	t_map		map;
}				t_data;
#endif
