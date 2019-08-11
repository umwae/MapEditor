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

static int			find_next_wall(t_core *cr, t_coord *cw, int prev, int secid)
{
	t_wall	*wall;

	wall = cr->wlist;
	if (!wall)
		return (-1);
	while (wall)
	{
		if (wall->p1.x == cw->x && wall->p1.y == cw->y && wall->index != prev && \
			(wall->sectors[0] == secid || wall->sectors[1] == secid))
		{
			cw->x = wall->p2.x;
			cw->y = wall->p2.y;
			return (wall->index);
		}
		else if (wall->p2.x == cw->x && wall->p2.y == cw->y && wall->index != prev && \
			(wall->sectors[0] == secid || wall->sectors[1] == secid))
		{
			cw->x = wall->p1.x;
			cw->y = wall->p1.y;
			return (wall->index);
		}
		wall = wall->next;
	}
	return (-1);
}

static void			find_any_wall_in_sec(t_core *cr, t_wall *wall, int refid, int pr2)
{
	(void)pr2;
	if (wall->sectors[0] == refid)
		cr->idcurr = wall->index;
	else if (wall->sectors[1] == refid)
		cr->idcurr = wall->index;
}

static void			record_sectors(t_core *cr, char *line, int fd)
{
	char		*tmp;
	char		*conn;
	int			i;
	t_coord	cw;
	int			curr;


	i = 0;
	tmp = NULL;
	conn = ft_strnew(100);

	while (i < cr->sec_num)
	{
		ft_putstr_fd(tmp = ft_strjoin("\ns|", ft_itoa(ST_FLOOR_HIGHT)), fd);
		free(tmp);
		ft_strcpy(line, " ");
    ft_putstr_fd(line, fd);
		ft_putstr_fd(tmp = ft_strjoin(ft_itoa(ST_CEIL_HIGHT), "|"), fd);
		free(tmp);
		//
		cr->idcurr = -1;
		iter_wall(cr, i, -1, &find_any_wall_in_sec);
		if (cr->idcurr != -1)
		{
			cw.x = find_by_index(cr, cr->idcurr)->p1.x;
			cw.y = find_by_index(cr, cr->idcurr)->p1.y;
			while ((curr = find_next_wall(cr, &cw, curr, i)) >= 0)
			{
				printf("IDCURR %d CURR %d\n", cr->idcurr, curr);
				ft_strcpy(line, ft_itoa(curr));
		    ft_putstr_fd(line, fd);
				if (find_by_index(cr, curr)->isportal == 1)
				{
					printf("%d IS PORTAL\n", curr);
					if (find_by_index(cr, curr)->sectors[0] == i)
					{
						printf("SEC No0 IS CURR SEC\n");
						// conn = ft_strcat(conn, " ");
						conn = ft_strcat(conn, ft_itoa(find_by_index(cr, curr)->sectors[1]));
					}
					else if (find_by_index(cr, curr)->sectors[1] == i)
					{
						printf("SEC No1 IS CURR SEC\n");
						// conn = ft_strcat(conn, " ");
						conn = ft_strcat(conn, ft_itoa(find_by_index(cr, curr)->sectors[0]));
					}
				}
				else
				{
					printf("%d IS NOT A PORTAL\n", curr);
					conn = ft_strcat(conn, "-1");
				}
				if (curr == cr->idcurr)
				{
					// conn = ft_strcat(conn, " -1");
					break ;
				}
				else
				{
					ft_strcpy(line, " ");
					conn = ft_strcat(conn, " ");
					ft_putstr_fd(line, fd);
				}
			}
		}
		ft_strcpy(line, "|");
		ft_putstr_fd(line, fd);
		ft_putstr_fd(conn, fd);
		ft_strclr(conn);
		ft_strcpy(line, "|");
		ft_putstr_fd(line, fd);
		i++;
	}
		ft_strcpy(line, "\n");
		ft_putstr_fd(line, fd);
		free(conn);
}

static void			record_walls(t_core *cr, char *line, int fd)
{
	t_wall	*wall;

	wall = cr->wlist;
	if (!wall)
		return;
	while (wall)
	{
    ft_strcpy(line, "v ");
    ft_putstr_fd(line, fd);
		ft_strcpy(line, ft_itoa(wall->p1.x));
    ft_putstr_fd(line, fd);
    ft_strcpy(line, " ");
    ft_putstr_fd(line, fd);
    ft_strcpy(line, ft_itoa(wall->p1.y));
    ft_putstr_fd(line, fd);
    ft_strcpy(line, " \n");
    ft_putstr_fd(line, fd);
    //
    ft_strcpy(line, "v ");
    ft_putstr_fd(line, fd);
    ft_strcpy(line, ft_itoa(wall->p2.x));
    ft_putstr_fd(line, fd);
    ft_strcpy(line, " ");
    ft_putstr_fd(line, fd);
    ft_strcpy(line, ft_itoa(wall->p2.y));
    ft_putstr_fd(line, fd);
    ft_strcpy(line, " \n");
    ft_putstr_fd(line, fd);
		wall = wall->next;
	}
}

void            save_map(t_core *cr)
{
  int   fd;
  char  *line;

  line = (char *)malloc(sizeof(char) * ft_strlen("v 0000 0000") + 1);
	fd = open("./maps/testmap", O_WRONLY | O_CREAT | O_TRUNC, 0777);
  record_walls(cr, line, fd);
	record_sectors(cr, line, fd);
	free(line);
	close(fd);
}
