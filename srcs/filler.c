/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnghondz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 16:30:30 by tnghondz          #+#    #+#             */
/*   Updated: 2018/07/03 14:56:08 by tnghondz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"
#include "../libft/libft.h"
#include "../includes/get_next_line.h"
#include <stdio.h>

void	init_player(int fd, t_player *player)
{
	char	*line;
	
	get_next_line(fd, &line);
	if((!(ft_strncmp(line, "$$$ exec p", 10))))
	{
		if(line[10] == '1')
		{
			player->id = '1';
			player->my_shape = 'O';
			player->current_shape = 'o';
		}
		else
		{
			player->id = '2';
			player->my_shape = 'X';
			player->current_shape = 'x';
		}
		ft_strdel(&line);
		return ;
	}
}

void	m_size(int fd, t_map_piece *map)
{
	char	*line;
	char	*x_pos;
	char	*y_pos;

	get_next_line(fd, &line);
	while(ft_strncmp(line, "Plateau ", 8))
		get_next_line(fd, &line);
	if(!(ft_strncmp(line, "Plateau ", 8)))
	{
		y_pos = ft_strchr(line, ' ');
		map->y_rows = ft_atoi(y_pos);
		y_pos++;
		x_pos = ft_strchr(y_pos, ' ');
		map->x_cols = ft_atoi(x_pos);
		free(line);
		return ;
	}
	
}
char **read_map(int fd, t_map_piece *read_map_into)
{
	char	**map;
	char	*begin;
	int		i;

	i = 0;
	if(!(map = (char**) malloc (sizeof(*map) * read_map_into->y_rows)))
		return(NULL);
	get_next_line(fd, &begin);
	while(ft_strncmp(begin, "000 ", 4))
		get_next_line(fd, &begin);
	while(i < (read_map_into->y_rows))
	{
		map[i] =  begin + 4;
		if(i < (read_map_into->y_rows - 1))
			get_next_line(fd, &begin);
		i++;
	}
	free(begin);
	return(map);
}


char **read_piece(int fd, t_map_piece *read_piece_into)
{
	char	**piece;
	char	*begin;
	int		i;

	i = 0;
	if(!(piece = (char**) malloc (sizeof(*piece) * read_piece_into->y_piece)))
		return(NULL);
	get_next_line(fd, &begin);
	while(ft_strncmp(begin, ".", 1) && ft_strncmp(begin, "*", 1))
		get_next_line(fd, &begin);
	while(i < (read_piece_into->y_piece))
	{
		piece[i] =  begin;
		if(i < (read_piece_into->y_piece - 1))
			get_next_line(fd, &begin);
		i++;
	}
	free(begin);
	return(piece);
}

void	piece_size(int fd, t_map_piece *piece)
{
	char	*line;
	char	*x_pos;
	char	*y_pos;

	get_next_line(fd, &line);
	while(ft_strncmp(line, "Piece ", 6))
		get_next_line(fd, &line);
	if(!(ft_strncmp(line, "Piece ", 6)))
	{
		y_pos = ft_strchr(line, ' ');
		piece->y_piece = ft_atoi(y_pos);
		y_pos++;
		x_pos = ft_strchr(y_pos, ' ');
		piece->x_piece = ft_atoi(x_pos);
		free(line);
		return ;
	}
}

void start_map(char **map, t_map_piece *m_info, t_player *me)
{
	int m_x;
	int m_y;

	m_y = 0;
	while(m_y < m_info->y_rows)
	{
		m_x = 0;
		while(map[m_y][m_x] != '\0')
		{
			if(map[m_y][m_x] == me->my_shape)
			{
				m_info->m_start_x = m_x;
				m_info->m_start_y = m_y;
				return ;
			}
			m_x++;
		}
		m_y++;
	}
}

void start_piece(char ** piece, t_map_piece *p_info)
{
	int p_x;
	int p_y;

	p_y = 0;
	while(p_y < p_info->y_piece)
	{
		p_x = 0;
		while(piece[p_y][p_x] != '\0')
		{
			if(piece[p_y][p_x] == '*')
			{
				p_info->p_start_x = p_x;
				p_info->p_start_y = p_y;
				return ;
			}
			p_x++;
		}
		p_y++;
	}
}


int main(int argc, char **argv)
{
	t_player *me;
	t_map_piece *map_size;
	int m = 0;
	int p = 0;

	char **map;
	char ** piece;
	
	if (argc == 1) return (0);
  	int fd = open(argv[1], O_RDONLY);
 	me = (t_player *) malloc (sizeof(*me));
	init_player(fd,me);
	map_size  = (t_map_piece *) malloc (sizeof(*map_size));
	m_size(fd, map_size);
	map = read_map(fd, map_size);
	piece_size(fd, map_size);
	piece = read_piece(fd, map_size);
	start_map(map, map_size, me);
	start_piece(piece, map_size);
	printf("map x: %i map y: %i\n",map_size->m_start_x, map_size->m_start_y);
	while(m < map_size->y_rows-1)
	{
		ft_putstr(map[m]);
		if(m != map_size->y_rows)
			ft_putchar('\n');
		m++;
	}
	while(p < map_size->y_piece)
	{
		ft_putstr(piece[p]);
	//	if(m != map_size->y_rows)
			ft_putchar('\n');
		p++;
	}
//	printf("%i %i\n", map_size->y_piece, map_size->x_piece);
 	close(fd);
}
