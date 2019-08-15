/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/26 19:43:26 by jsteuber         ###   ########.fr       */
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

static void     process_walls(t_core *cr, char **pts, int secnum)
{
  t_coord inp1;
  t_coord inp2;
  int     i;
  int     fd2;
  char    *line;
  int     num;
  char    **v;
  int     j;
  //
  t_wall  *wall;

//Почему-то close не сбрасывает положение в тексте и после переоткрытия файл читается не с начала
  i = 0;
  while (pts[i + 1])
  {
    num = ft_atoi(pts[i]);
    printf("num %d\n", num);
    fd2 = open("./maps/testmap", O_RDONLY);
    j = 0;
    while (j++ <= num)
    {
      get_next_line(fd2, &line);
      printf("v pos: %s, num: %d, j: %d, fd; %d\n", line, num, j, fd2);
      if (j <= num)
        free(line);
    }
    v = ft_strsplit(line, ' ');
    printf("atoi %s %s\n", v[1], v[2]);
    inp1.x = ft_atoi(v[1]);
    inp1.y = ft_atoi(v[2]);
    ft_arrfree(&v, 3);
    num = ft_atoi(pts[i + 1]);
    printf("num2 %d\n", num);
    // close(fd2);
    fd2 = open("./maps/testmap", O_RDONLY);
    j = 0;
    while (j++ <= num)
    {
      get_next_line(fd2, &line);
      printf("v2 pos: %s, num: %d, j: %d, fd: %d\n", line, num, j, fd2);
      if (j <= num)
        free(line);
    }
    v = ft_strsplit(line, ' ');
    printf("atoi2 %s %s\n", v[1], v[2]);
    inp2.x = ft_atoi(v[1]);
    inp2.y = ft_atoi(v[2]);
    ft_arrfree(&v, 3);
    // close(fd2);
    if (check_dups(cr, inp1, inp2) == 0)
    {
      printf("Dups OK. secnum: %d\n", secnum);
      cr->vs.mem_x = inp1.x;
      cr->vs.mem_y = inp1.y;
      cr->vs.x1 = inp2.x;
      cr->vs.y1 = inp2.y;
      add_wall(cr);
      wall = get_last_wall(cr);
      if (wall->sectors[0] == -1)
        wall->sectors[0] = secnum;
      else if (wall->sectors[1] == -1)
        wall->sectors[1] = secnum;
    }
    // else
    //   set_portal(cr, inp1, inp2);
    i++;
  }
}

void            load_map(t_core *cr)
{
  int   fd;
  char  *line;
	int		i;
  char  **pts;
  char  *tmp;

  delete_wlist(cr);
	fd = open("./maps/testmap", O_RDONLY);
	cr->mpsw = 0;
	i = -1;
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 's')
		{
      if (i == -1)
        i = 0;
      tmp = ft_strsub(line, find_rep_symb(line, '|', 2) + 1, \
      find_rep_symb(line, '|', 3) - (find_rep_symb(line, '|', 2) + 1));
      printf("%s\n", tmp);
      tmp = ft_strjoin(tmp, " ");
      tmp = ft_strjoin(tmp, ft_strsub(line, find_rep_symb(line, '|', 2) + 1, \
      find_rep_symb(line, ' ', 2) - (find_rep_symb(line, '|', 2) + 1)));
      printf("%s\n", tmp);
			pts = ft_strsplit(tmp, ' ');
      process_walls(cr, pts, i);
      free(tmp);
      i++;
		}
    free(line);
	}
  // load_walls(cr, line, fd);
	// load_sectors(cr, line, fd);
  // load_portals(cr, line, fd);
  iter_wall(cr, -1, -1, &redraw_color);
	free(line);
	close(fd);
}
