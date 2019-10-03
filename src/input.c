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

void     process_walls(t_core *cr, char **pts, char **prt, int secnum)
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
    printf(">>>>>>>>>>444>>>>>>>>>>> %d\n", fd2);
    j = 0;
    while (j++ <= num)
    {
      if (get_next_line(fd2, &line) <= 0)
        err_ex(1);
      // printf(">>>>>>>>>>11>>>>>>>>>>> %s\n", line);
      if (j < num + 1)
        free(line);
    }
    v = ft_strsplit(line, ' ');
    free(line);
	  inp1.x = ft_atof(v[2]) * cr->zoom / UNIT_SIZE;
	  inp1.y = ft_atof(v[1]) * cr->zoom / UNIT_SIZE;
    ft_arrfree(&v, 3);
    num = ft_atoi(pts[i + 1]);
    // close (fd2);
    if ((fd2 = open("./maps/testmap", O_RDONLY)) == -1)
      reopen_10_times(&fd2);
    printf(">>>>>>>>>>555>>>>>>>>>>> %d\n", fd2);
    j = 0;
    while (j++ <= num)
    {
      if (get_next_line(fd2, &line) <= 0)
        err_ex(1);
      // printf(">>>>>>>>>22>>>>>>>>>>>> %s\n", line);
      if (j < num + 1)
        free(line);
    }
    v = ft_strsplit(line, ' ');
    free(line);
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

void		load_doors(t_core *cr)
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

void		load_finish(t_core *cr)
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

// static void     debtest(t_core *cr)
// {
//   char  *line;
//   int   fd;

//   fd = open("./maps/testmap", O_RDONLY);
//   while (get_next_line(fd, &line) > 0)
// 	{
//     printf("%s\n", line);
//     free(line);
//   }
//   close(fd);
//   free(line);
//   printf("--------------------------------------------\n");
//   fd = open("./maps/testmap", O_RDONLY);
//   while (get_next_line(fd, &line) > 0)
// 	{
//     printf("%s\n", line);
//     free(line);
//   }
//   free(line);
// }
