/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:32:17 by tfalchi           #+#    #+#             */
/*   Updated: 2024/05/09 17:39:05 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_character {
	void	*img;
	int		with;
	int		height;
	int		x; //witdh_matrix;
	int		y; //height_matrix;
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

typedef struct	s_data {
	t_assets	img;
	char		**matrix;
	
}				t_data;
#endif
