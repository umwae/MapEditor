/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/11 19:54:22 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdio.h"
#include <fcntl.h>
#include "stdlib.h"
#include "math.h"

int     find_rep_symb(char *line, char symb, int num)
{
  char  *p;

  p = line;
  while (num--)
  {
    p = ft_strchr(p + 1, symb);
  }
  return (p - line);
}

static void     delete_wlist(t_core *cr)
{
  while (cr->wlist)
    erase_by_id(cr, 0);
}

static int      check_dups(t_core *cr, t_coord inp1, t_coord inp2)
{
  t_wall  *wall;

  wall = cr->wlist;
  if (!wall)
    return (0);
  while (wall)
  {
    if (((inp1.x == wall->p1.x && inp1.y == wall->p1.y) && (inp2.x == wall->p2.x && inp2.y == wall->p2.y)) || \
    ((inp1.x == wall->p2.x && inp1.y == wall->p2.y) && (inp2.x == wall->p1.x && inp2.y == wall->p1.y)))
      return (1);
    wall = wall->next;
  }
  return (0);
}

static void     set_sectors(t_core *cr, t_coord inp1, t_coord inp2, int secnum)
{
	t_wall  *wall;

    wall = cr->wlist;
    if (!wall)
      return ;
    while (wall)
    {
      if (((inp1.x == wall->p1.x && inp1.y == wall->p1.y) && (inp2.x == wall->p2.x && inp2.y == wall->p2.y)) || \
      ((inp1.x == wall->p2.x && inp1.y == wall->p2.y) && (inp2.x == wall->p1.x && inp2.y == wall->p1.y)))
      {
		  if (wall->sectors[0] == -1)
			wall->sectors[0] = secnum;
		  else if (wall->sectors[1] == -1)
			wall->sectors[1] = secnum;
	  }
      wall = wall->next;
    }
}

static void     process_walls(t_core *cr, char **pts, char **prt, int secnum)
{
  t_coord inp1;
  t_coord inp2;
  int     i;
  int     fd2;
  char    *line;
  int     num;
  char    **v;
  int     j;

//Почему-то close не сбрасывает положение в тексте и после переоткрытия файл читается не с начала
  i = 0;
  while (pts[i + 1])
  {
    num = ft_atoi(pts[i]);
    fd2 = open("./maps/testmap", O_RDONLY);
    j = 0;
    while (j++ <= num)
    {
      get_next_line(fd2, &line);
      if (j <= num)
        free(line);
    }
    v = ft_strsplit(line, ' ');
	inp1.x = ft_atof(v[2]) * cr->zoom / UNIT_SIZE;
	inp1.y = ft_atof(v[1]) * cr->zoom / UNIT_SIZE;
    ft_arrfree(&v, 3);
    num = ft_atoi(pts[i + 1]);
    fd2 = open("./maps/testmap", O_RDONLY);
    j = 0;
    while (j++ <= num)
    {
      get_next_line(fd2, &line);
      if (j <= num)
        free(line);
    }
    v = ft_strsplit(line, ' ');
	inp2.x = ft_atof(v[2]) * cr->zoom / UNIT_SIZE;
	inp2.y = ft_atof(v[1]) * cr->zoom / UNIT_SIZE;
    ft_arrfree(&v, 3);
    if (check_dups(cr, inp1, inp2) == 0)
    {
      cr->vs.mem_x = inp1.x;
      cr->vs.mem_y = inp1.y;
      cr->vs.x1 = inp2.x;
      cr->vs.y1 = inp2.y;
      if (ft_atoi(prt[i + 1]) >= 0)
        cr->mpsw = 1;
      add_wall(cr);
    }
	set_sectors(cr, inp1, inp2, secnum);
    i++;
  }
}

void            load_map(t_core *cr)
{
  int   fd;
  char  *line;
	int		i;
  char  **pts;
  char  **prt;
  char  *tmp;
  char	*p;

	cr->sec_num = 0;
  delete_wlist(cr);
	fd = open("./maps/testmap", O_RDONLY);
	// cr->mpsw = 0;
	i = -1;
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 's')
		{
			if (i == -1)
				i = 0;
			// s|0.00 75.00|2 1 0 3|-1 -1 1 -1|


			p = line + find_rep_symb(line, '|', 3);
	  	  while (*p != ' ')
	  	  	p--;
	  	printf("PPPPPPPP %s //////// %s\n", line, ft_strsub(p + 1, 0, ft_strchr(p, '|') - p - 1));
	  	  tmp = ft_strsub(p + 1, 0, ft_strchr(p, '|') - p - 1);
	  	  tmp = ft_strjoin(tmp, " ");
	  	  tmp = ft_strjoin(tmp, ft_strsub(line, find_rep_symb(line, '|', 2) + 1, \
	  			find_rep_symb(line, '|', 3) - (find_rep_symb(line, '|', 2) + 1)));
	  		printf("TTTTTTTT %s\n", tmp);
	        pts = ft_strsplit(tmp, ' ');
			ft_strclr(tmp);
		//
	  p = line + find_rep_symb(line, '|', 4);
	  while (*p != ' ')
	  	p--;
	printf("PPPPPPPP %s //////// %s\n", line, ft_strsub(p + 1, 0, ft_strchr(p, '|') - p - 1));
	  tmp = ft_strsub(p + 1, 0, ft_strchr(p, '|') - p - 1);
	  tmp = ft_strjoin(tmp, " ");
	  tmp = ft_strjoin(tmp, ft_strsub(line, find_rep_symb(line, '|', 3) + 1, \
			find_rep_symb(line, '|', 4) - (find_rep_symb(line, '|', 3) + 1)));
		printf("TTTTTTTT %s\n", tmp);
      prt = ft_strsplit(tmp, ' ');
			ft_strclr(tmp);
      //
      process_walls(cr, pts, prt, i);
			i++;
		}
		// free(line);
	}
  // load_walls(cr, line, fd);
	// load_sectors(cr, line, fd);
  // load_portals(cr, line, fd);
  load_player(cr, &line);
  iter_wall(cr, -1, -1, &count_sectors);
  iter_wall(cr, -1, -1, &redraw_color);
	// free(line);
	close(fd);
}
