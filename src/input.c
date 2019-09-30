/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/19 20:01:46 by jsteuber         ###   ########.fr       */
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
		  if (wall->sectors[0].s == -1)
			wall->sectors[0].s = secnum;
		  else if (wall->sectors[1].s == -1)
			wall->sectors[1].s = secnum;
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
    if ((fd2 = open(SAVEPATH, O_RDONLY)) == -1)
      reopen_10_times(&fd2);
    j = 0;
    while (j++ <= num)
    {
      if (get_next_line(fd2, &line) <= 0)
        err_ex(1);
      if (j <= num)
        free(line);
    }
    v = ft_strsplit(line, ' ');
	inp1.x = ft_atof(v[2]) * cr->zoom / UNIT_SIZE;
	inp1.y = ft_atof(v[1]) * cr->zoom / UNIT_SIZE;
    ft_arrfree(&v, 3);
    num = ft_atoi(pts[i + 1]);
    // close (fd2);
    if ((fd2 = open("./maps/testmap", O_RDONLY)) == -1)
      reopen_10_times(&fd2);
    j = 0;
    while (j++ <= num)
    {
      if (get_next_line(fd2, &line) <= 0)
        err_ex(1);
      if (j <= num)
        free(line);
    }
    v = ft_strsplit(line, ' ');
    // close (fd2);
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

static void		load_doors(t_core *cr)
{
	int			fd;
	char		*line;

	if ((fd = open("./maps/testmap", O_RDONLY)) == -1)
      reopen_10_times(&fd);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'd')
			find_sec_list(cr, ft_atoi(line + 2))->isdoor = 1;
		free(line);
	}
	close(fd);
	free(line);
	return ;
}

static void		load_finish(t_core *cr)
{
	int			fd;
	char		*line;

	if ((fd = open("./maps/testmap", O_RDONLY)) == -1)
      reopen_10_times(&fd);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'f')
			find_sec_list(cr, ft_atoi(line + 2))->isfinish = 1;
		free(line);
	}
	close(fd);
	free(line);
	return ;
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

  // load_sec_list(cr);
	//
	cr->sec_num = 0;
  delete_wlist(cr);
	if ((fd = open("./maps/testmap", O_RDONLY)) == -1)
      reopen_10_times(&fd);
	// cr->mpsw = 0;
	i = -1;
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 's')
		{
			cr->sec_num++;
      printf("SEC_NUM++\n");
			if (i == -1)
				i = 0;
			// s|0.00 75.00|2 1 0 3|-1 -1 1 -1|
			add_sec_list(cr);
			pts = ft_strsplit(line, '|');
      		// find_sec_list(cr, i)->floor = 99;
			find_sec_list(cr, i)->floor = ft_atof(pts[1]);
			find_sec_list(cr, i)->ceiling = ft_atof(ft_strchr(pts[1], ' ') + 1);
			if (pts[4])
      {
        // for (size_t h = 0; pts[h]; h++)
        // {
        //   printf("pts4 %s\n", pts[h]);
        // }
        fflush(stdout);
        find_sec_list(cr, i)->illum = ft_atof(pts[4]);
      }
			free(pts);
			//
			p = line + find_rep_symb(line, '|', 3);
	  	while (*p != ' ')
	  	  p--;
	  	tmp = ft_strsub(p + 1, 0, ft_strchr(p, '|') - p - 1);
	  	tmp = ft_strjoin(tmp, " ");
	  	tmp = ft_strjoin(tmp, ft_strsub(line, find_rep_symb(line, '|', 2) + 1, \
	  	find_rep_symb(line, '|', 3) - (find_rep_symb(line, '|', 2) + 1)));
	    pts = ft_strsplit(tmp, ' ');
			ft_strclr(tmp);
		//
	    p = line + find_rep_symb(line, '|', 4);
	    while (*p != ' ')
	  	  p--;
	    tmp = ft_strsub(p + 1, 0, ft_strchr(p, '|') - p - 1);
	    tmp = ft_strjoin(tmp, " ");
	    tmp = ft_strjoin(tmp, ft_strsub(line, find_rep_symb(line, '|', 3) + 1, \
			find_rep_symb(line, '|', 4) - (find_rep_symb(line, '|', 3) + 1)));
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
  load_sec_info(cr);
  while (*cr->olist)
  	del_object(cr, 0);
load_objects(cr);
  load_player(cr, &line);
  iter_wall(cr, -1, -1, &count_sectors);
  iter_wall(cr, -1, -1, &redraw_color);
  load_doors(cr);
  load_finish(cr);
	// free(line);
	close(fd);
}
