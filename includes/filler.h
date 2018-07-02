/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnghondz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 16:24:15 by tnghondz          #+#    #+#             */
/*   Updated: 2018/07/02 12:39:45 by tnghondz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
#define FILLER_H

#include "../libft/libft.h"

typedef struct	s_player
{
	char		id;
	char		my_shape;
	char		current_shape;
}				t_player;

typedef struct	s_map_piece
{
	int x_cols;
	int y_rows;
	int	x_piece;
	int	y_piece;
}				t_map_piece;
#endif
