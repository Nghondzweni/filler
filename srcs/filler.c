/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnghondz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 16:30:30 by tnghondz          #+#    #+#             */
/*   Updated: 2018/07/25 09:29:41 by tnghondz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/filler.h"
#include "../libft/libft.h"
#include "../includes/get_next_line.h"
#include <stdio.h>

void	init_player(t_player *player)
{
	char	*line;
//	while(ft_strncmp(line, "$$$ exec p", 10))
		get_next_line(0, &line);
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
	return ;
}

void place_piece(t_map_piece *info, t_player *me)
{
    int p_y;
    int p_x;
    int m_x;
    int m_y;

	info->place_ret = 0;
    p_y = info->y_piece - 1;
    m_y = info->y_place - 1;
    while(p_y >= 0)
    {
		if (info->y_place - info->y_piece < 0)
		{
			info->place_ret = 2;
			return ;
		}
    	m_x = info->x_place - 1;
        p_x = info->x_piece - 1;
        while(p_x >= 0)
        {
	//		ft_putchar(info->map[m_y][m_x]);
            if(info->x_place - info->x_piece < 0)
			{
				info->place_ret = 1;
				return ;
			}
            if(info->piece[p_y][p_x] != '.')
                info->temp_map[m_y][m_x] = me->my_shape;
			info->place_coordinate_x = m_x;
			info->place_coordinate_y = m_y;
            m_x--;
            p_x--;
        }
        m_y--;
        p_y--;
    }
}

void	m_size(t_map_piece *map)
{
	char	*line;
	char	*x_pos;
	char	*y_pos;

	get_next_line(0, &line);
	while(ft_strncmp(line, "Plateau ", 8))
		get_next_line(0, &line);
	if(!(ft_strncmp(line, "Plateau ", 8)))
	{
		y_pos = ft_strchr(line, ' ');
		map->y_rows = ft_atoi(y_pos);
		map->y_place = map->y_rows;
		y_pos++;
		x_pos = ft_strchr(y_pos, ' ');
		map->x_cols = ft_atoi(x_pos);
		map->x_place = map->x_cols;
		free(line);
		return ;
	}

}
void read_map(t_map_piece *read_map_into)
{ 
	char	**map;
	char	*begin;
	int		i;
	int		x;
	int		m;

	i = 0;
	m = 0;

	if(!(read_map_into->map = (char**) malloc (sizeof(*map) * read_map_into->y_rows)))
		return ;
	get_next_line(0, &begin);
	while(ft_strncmp(begin, "000 ", 4))
	{
		get_next_line(0, &begin);
	}
	while(i < (read_map_into->y_rows))
	{
		//map[i] = begin + 4;zsh: segmentation fault  ./a.out < ../../sr
		x = 0;
		read_map_into->map[i] = (char *) malloc(sizeof(char) * read_map_into->x_cols + 1);
		while(x < read_map_into->x_cols)
		{
			read_map_into->map[i][x] = begin [x + 4];
			x++;
		}
		read_map_into->map[i][x] = '\0';
//		ft_putchar(read_map_into->map[i][x]);
		if(i < (read_map_into->y_rows - 1))
			get_next_line(0, &begin);
		i++;
	}
//	free(begin);
//	read_map_into->map = map;
}

void	copy_tmp_map(t_map_piece *read_tmp_into)
{
	int x;
	int y;

	x = 0;
	y = 0;
	if(!(read_tmp_into->temp_map = (char**) malloc (sizeof(char *) * read_tmp_into->y_rows)))
		return ;
	while(y < read_tmp_into->y_rows)
	{
		x = 0;
		read_tmp_into->temp_map[y] = (char *) malloc (sizeof(char) * read_tmp_into->x_cols);
		while(x < read_tmp_into->x_cols)
		{
			read_tmp_into->temp_map[y][x] = read_tmp_into->map[y][x];	
			x++;
		}
		y++;
	}
}

void	read_piece(t_map_piece *read_piece_into)
{
	char	**piece;
	char	*begin;
	int		i;
	int		x;

	i = 0;
	if(!(read_piece_into->piece = (char**) malloc (sizeof(*piece) * read_piece_into->y_piece)))
		return ;
	get_next_line(0, &begin);
	while(ft_strncmp(begin, ".", 1) && ft_strncmp(begin, "*", 1))
		get_next_line(0, &begin);
	while(i < (read_piece_into->y_piece))
	{
		x = 0;		
		read_piece_into->piece[i] = (char *) malloc(sizeof(char) * read_piece_into->x_piece + 1);
		while(x < read_piece_into->x_piece)
		{
			read_piece_into->piece[i][x] = begin[x];
			x++;
		}
		read_piece_into->piece[i][x] = '\0';
	//	read_piece_into->piece[i] = begin;
		//ft_putstr(read_piece_into->piece[i]);
//		ft_putstr(begin);
		if(i < (read_piece_into->y_piece - 1))
			get_next_line(0, &begin);
		i++;
	}
//	free(begin);
//	read_piece_into->piece = piece;
}

void	piece_size(t_map_piece *piece)
{
	char	*line;
	char	*x_pos;
	char	*y_pos;

	get_next_line(0, &line);
	while(ft_strncmp(line, "Piece ", 6))
		get_next_line(0, &line);
	i\f(!(ft_strncmp(line, "Piece ", 6)))
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
/*
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
		printf("%i\n", i);
	while(p_y < p_info->y_piece)
	{
		p_x = 0;
		while(piece[p_y][p_x] != '\0')
		{
			if(piece[p_y][p_x] == '*')
			{
				p_info->p_first_x = p_x;
				p_info->p_first_y = p_y;
				return ;
			}
			p_x++;
		}
		p_y++;
	}
}
*/
void get_shape_num_p(t_map_piece *p_info)
{
	int x;
	int y;
	int shapes;

	y = 0;
	shapes = 0;
	while(y < p_info->y_piece)
	{
		x = 0;
		while(x < p_info->x_piece)
		{
			if(p_info->piece[y][x] == '*')
				shapes++;
			x++;
		}
		y++;
	}
	p_info->add_num = shapes;
}

void get_os_xs_num(t_map_piece *p_info)
{
    int x;
    int y;
    int os;
	int xs;

    y = 0;
    os = 0;
	xs = 0;
    while(y < p_info->y_rows)
    {
        x = 0;
        while(x < p_info->x_cols)
        {
            if(p_info->map[y][x] == 'O' || p_info->map[y][x] == 'o')
                os++;
			else if(p_info->map[y][x] == 'X' || p_info->map[y][x] == 'x')
				xs++;
            x++;
        }
        y++;
    }
    p_info->os_num = os;
	p_info->xs_num = xs;
}


void get_temp_os_xs(t_map_piece *p_info)
{
    int x;
    int y;
    int os;
	int xs;

    y = 0;
    os = 0;
	xs = 0;
    while(y < p_info->y_rows)
    {
        x = 0;
        while(x < p_info->x_cols)
        {
            if(p_info->temp_map[y][x] == 'O' || p_info->temp_map[y][x] == 'o')
                os++;
			else if(p_info->temp_map[y][x] == 'X' || p_info->temp_map[y][x] == 'x')
				xs++;
            x++;
        }
        y++;
    }
    p_info->temp_os = os;
	p_info->temp_xs = xs;
}
/*
void find_left_start_p(char **piece, t_map_piece *info)
{	while(m < info->y_rows)
    	{
			printf("%s\n", info->temp_map[m]);
			m++;
		}


	int	x;
	int	y;

	x = 0;
	while(x < info->x_piece)
	{
char **map;
	char ** piece;
		y = 0;  			while(m < info->y_rows)
    		{
       			 printf("%s\n", info->temp_map[m]);
       	 		m++;
    		}

		while(y < info->y_piece)
		{
			if(piece[y][x] == '*')
			{
				info->p_left_start = x;
				return ;
			}
			y++;
		}
		x++;
	}
}
char **map;
	char ** piece;

void find_top_start_p(char **piece, t_map_piece *info)
{
	int	x;
	int	y;

	y = 0;
	while(y < info->y_piece)
	{
		x = 0;
            ft_putchar('\n');
		while(x < info->y_piece)void get_os_num(char **map, t_map_piece *p_info)
		{
			if(piece[y][x] == '*')
			{
				info->p_top_start = y;
				return ;
			}  	while(m < map_size->y_rows)
    {

        printf("%s\n", map_size->temp_map[m]);
        m++;
    }

			x++;
		}
		y++;
	}
}

void find_right_end_p(char **piece, t_map_piece *info)
{
	int	x;
	int	y;

	x = info->x_piece - 1;
	while(x > 0)
	{
		y = info->y_piece - 1;
		while(y > 0)
		{
			if(piece[y][x] == '*')
			{
				info->p_right_end = x;
				return ;
			}
			y--;
		}
		x--;
	}
}

void find_bottom_end_p(char **piece, t_map_piece *info)
{
	int	x;
	int	y;

	x = info->x_piece - 1;
 	while(x > 0)
	{
		y = info->y_piece - 1;
		while(y > 0)
		{
			if(piece[y][x] == '*')
			{
				info->p_bottom_end = y;
				return ;
			}->my_shape;
				info->place_coordinate_x = m_x;
				info->place_coordinate_y = m_y;
            
			y--;
		}
		x--;
	}
}
*/

/*int place_piece(char **map, char **piece, t_map_piece *mp_info, t_player *me)
{
	int x_m;
	int y_m;
	int x_p;
	int y_p;
	int p_shapes;

	while(y_p < mp_info->y_piece)
	{
		x_p = 0;
		while(x_p < mp_info->x_piece)
		{
			if(piece[y_p][x_p] == '*' && map[m_start_y + y_p][m_start_x + x_p] == '.')
			{
				map[m_start_y + y_p][m_start_x + x_p] = me->my_shape;
				p_shapes--;
			}
			else
			{
				m_start_x++;
				start_map(map, mp_info, me);
			}
		}
	}
}
*/
int    check_placement(t_map_piece *p_info, t_player *shape)
{
    if (shape->my_shape == 'O')
    {
        if ((p_info->os_num + p_info->add_num - 1) == p_info->temp_os &&
				  (p_info->xs_num == p_info->temp_xs))
		{
		//	printf("os num: %i add_num: %i temp_os: %i xs_num: %i temp_xs: %i  \n", p_info->os_num , p_info->add_num, p_info->temp_os, p_info->xs_num,  p_info->temp_xs);
			return (0);
		}
        else
		{
		//	printf("os num: %i add_num: %i temp_os: %i xs_num: %i temp_xs: %i  \n", p_info->os_num , p_info->add_num, p_info->temp_os, p_info->xs_num,  p_info->temp_xs);
			return (1);
		}
    }
    else if (shape->my_shape == 'X')
    {
	        if ((p_info->xs_num + p_info->add_num - 1) == p_info->temp_xs &&
                (p_info->os_num == p_info->temp_os))
			return (0);
        else
			return (1);
    }
    return (-1);
}

int    move(t_map_piece *info)
{
   if (info->place_ret == 1)
   {
       info->y_place--;
       info->x_place = info->x_cols - 1;
	   info->x_place++;
   }
   else if (info->place_ret == 2)
   {
       return (1);
   }
   else
   {
	   info->x_place--;
   }
   return (0);
}

void    send_coordinate(t_map_piece *info, t_player *me)
{
	/*   ft_putnbr(3);
	ft_putchar(' ');
	ft_putnbr(3);
	ft_putchar('\n');*/
	ft_putnbr(info->place_coordinate_y);
	ft_putchar(' ');
	ft_putnbr(info->place_coordinate_x);
	ft_putchar('\n');
		//ft_putendl(ft_itoa(y), ft_itoa(x));
}
/*
char **init_temp(t_map_piece *info)
{
    int     i;
    int     m;
    char    **temp;

	if(!(temp = (char**) malloc (sizeof(*temp) * info->y_rows)))
        return (NULL);
    m = 0;
    while (m < info->y_rows)
    {
          temp[m] = info->map[m];
	//	  printf("%s", info->map[m]);
        m++;
    }
    return (temp);
}
*/
/*int	algo(t_map_piece *info, t_player *me)
{
	int	m = 0;
	char **temp;
	
	//	temp = init_temp(info);
//	info->temp_map = info->map;i
	
 //   m_size(info);
 // 	read_map(info);
   // piece_size(info);
  //  read_piece(info);
    copy_tmp_map(info);

	get_shape_num_p(info);
	place_piece(info, me);
	get_os_xs_num(info);
	get_temp_os_xs(info);

	
	if(!(check_placement(info, me)))
	{
		send_coordinate(info, me);
		while(m < info->y_rows)
    	{
			printf("%s\n", info->temp_map[m]);
			m++;
		}

		return (0);
	}
	else
	{
		if (!move(info))
		{
  			while(m	while(m < info->y_rows)
    	{
			printf("%s\n", info->temp_map[m]);
			m++;
		}

 < info->y_rows)
    		{
       			 printf("%s\n", info->temp_map[m]);
       	 		m++;
    		}
//			ft_putchar('a');
			while(m < info->y_rows)
			{
				ft_putstr(info->temp_map[m]);
				ft_putchar('\n');
				m++;
			}
			copy_tmp_map(info);
//			return (1);
//			temp = info->map;
		//	ft_strdel(info->temp_map);
	//		ft_strdel(temp);
			algo(info, me);
		}
//		else
//						ft_putchar('a');
return (0);
	}
	return(0);
}*/
/*
void	algo_loop(t_map_piece *info, t_player *me)
{
	while ((algo(info, me) != 0))
		info->temp_map = info->map;
}
*/

void	init_struct(t_map_piece *info)
{
	info->x_place = 0;
	info->y_place = 0;
	info->place_ret = 0;

	info->add_num = 0;
	info->os_num = 0;
	info->xs_num = 0;
	info->temp_os = 0;
	info->temp_xs = 0;

//	info->map = NULL;
//	info->piece = NULL;
//	info->temp_map = NULL;

	info->place_coordinate_x = 0;
	info->place_coordinate_y = 0;


}


int main(int argc, char **argv)
{
    t_player *me;
    t_map_piece *map_size;
	char *buff;
    int m = 0;
    int p = 0;
    int t = 0;
	int rd = 0;

 //   if (argc == 1) return (0);
   // int fd = open(argv[1], O_RDONLY);
    me = (t_player *) malloc (sizeof(*me));
    init_player(me);
    map_size  = (t_map_piece *) malloc (sizeof(*map_size));
   	m_size(map_size);
   	read_map(map_size);
    piece_size(map_size);
  	read_piece(map_size);
 	copy_tmp_map(map_size);
/*    get_shape_num_p(map_size);
    get_os_xs_num(map_size);
    get_temp_os_xs(map_size);
    printf("%d %d %d %d %d\n", map_size->add_num, map_size->os_num, map_size->xs_num, map_size->temp_os, map_size->temp_xs);
    check_placement(map_size, me);
    printf("%d ", map_size->check);
	start_map(map, map_size, me);
	start_piece(piece, map_size);
  	printf("map x: %i map y: %i\n",map_size->x_cols, map_size->y_rows);
  */
  /*  while(m < map_size->y_rows)
    {
        printf("%s\n", map_size->map[m]);
        m++;
    }
*/
//	place_piece(map_size, me);

//	ft_putchar('\n');
/*
	while(t < map_size->y_rows)
    {
        ft_putstr(map_size->temp_map[t]);
   //     if(t != map_size->y_rows)
            ft_putchar('\n');
        t++;
    }
  */
//    m = 0;
 /*
  	while(m < map_size->y_rows)
    {

        printf("%s\n", map_size->temp_map[m]);
        m++;
    }
*/
/*
			ft_putchar('d');
    while(p < map_size->y_piece)
    {
        ft_putstr(map_size->piece[p]);
      if(m != map_size->y_rows)
            ft_putchar('\n');
        p++;
    }

*/
/*  find_left_start_p(piece, map_size);
    find_bottom_end_p(piece, map_size);
    find_top_start_p(piece, map_size);
    find_right_end_p(piece, map_size);
    printf("left start: %i, top start: %i, right end: %i, bottom end: %i", map_size->p_left_start, map_size->p_top_start, map_size->p_right_end, map_size->p_bottom_end);*/
//  ft_putnbr(get_shape_num_p(piece, map_size));
//  printf("%i %i\n", map_size->y_piece, map_size->x_piece);
	while(1)
	{
    copy_tmp_map(map_size);

	get_shape_num_p(map_size);
//	ft_putnbr(map_size->add_num);
	place_piece(map_size, me);
	get_os_xs_num(map_size);
//	ft_putnbr(map_size->os_num);
//	ft_putnbr(map_size->xs_num);
	get_temp_os_xs(map_size);
//	ft_putnbr(map_size->temp_os);
//	ft_putchar('a');

	
	if(!(check_placement(map_size, me)))
	{
		send_coordinate(map_size, me);
		map_size->y_place = map_size->y_rows - 1;
//		ft_putchar('b');
		if (rd > 0)
		{
			free(map_size->map);
			read_map(map_size);
		//	ft_putchar('c');
			map_size->x_piece = 0;
			map_size->y_piece = 0;
		//	ft_putchar('v');
			piece_size(map_size);
		//	ft_putnbr(map_size->x_piece);
		//	ft_putnbr(map_size->y_piece);
			free(map_size->piece);
			read_piece(map_size);
		//	ft_putchar('T');

		}

	}
	else
	{
		if (!move(map_size))
		{
			copy_tmp_map(map_size);
		rd++;	
		}
		else
			{
				ft_putnbr(0);
				ft_putchar(' ');
				ft_putnbr(0);
				ft_putchar('\n');
			}

//	}
//	rd++;
//	ft_putchar('G');


	//	read_map(map_size);
	//	read_piece(map_size);		


//	init_temp(map_size);
  //  close(fd);
}
}
}
