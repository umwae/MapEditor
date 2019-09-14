/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/14 17:40:14 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdio.h"
#include <fcntl.h>
#include "stdlib.h"
#include "math.h"

int			find_vt_id(t_core *cr, float x, float y)
{
	int		fd;
	char	*line;
	int		i;

	(void)cr;
	// printf("looking for v id: %f %f\n", x, y);
	fd = open("./maps/testmap", O_RDONLY);
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] != 'v')
			return (0);
		if (ft_atof(line + 2) == y && \
		ft_atof(line + find_rep_symb(line, ' ', 2) + 1) == x)
			return (i);
		i++;
	}
	return (0);
}

static void			choose_direction(t_core *cr, t_fcoord *cw, t_wall *start, int secid)
{
	t_wall		*wall;
	t_coord		p3;
	int				side;

	wall = cr->wlist;
	if (!wall)
		return ;
	while (wall)
	{
		if (wall->p1.x == start->p1.x && wall->p1.y == start->p1.y && wall->index != start->index && \
			(wall->sectors[0] == secid || wall->sectors[1] == secid))
		{
			printf("START %d W ID%d P1\n", start->index, wall->index);
			p3 = wall->p2;
			break ;
		}
		else if (wall->p2.x == start->p1.x && wall->p2.y == start->p1.y && wall->index != start->index && \
			(wall->sectors[0] == secid || wall->sectors[1] == secid))
		{
			printf("START %d W ID%d P2\n", start->index, wall->index);
			p3 = wall->p1;
			break ;
		}
		wall = wall->next;
	}
	if ((side = (start->p1.x - start->p2.x) * (p3.y - start->p2.y) - \
	(start->p1.y - start->p2.y) * (p3.x - start->p2.x)) > 0)
	{
		cw->x = start->p1.x / cr->zoom * UNIT_SIZE;
		cw->y = start->p1.y / cr->zoom * UNIT_SIZE;
	}
	else if (side < 0)
	{
		cw->x = start->p2.x / cr->zoom * UNIT_SIZE;
		cw->y = start->p2.y / cr->zoom * UNIT_SIZE;
	}
	// else
	// 	choose_direction(cr, cw, find_by_index(cr, ), int secid)
	printf("SIDE: %d\n", side);
}

static int			find_next_wall(t_core *cr, t_fcoord *cw, int prev, int secid)
{
	t_wall	*wall;

	wall = cr->wlist;
	if (!wall)
		return (-1);
	while (wall)
	{
		if (wall->p1.x == cw->x * cr->zoom / UNIT_SIZE && wall->p1.y == cw->y * cr->zoom / UNIT_SIZE && wall->index != prev && \
			(wall->sectors[0] == secid || wall->sectors[1] == secid))
		{
			cw->x = wall->p2.x / cr->zoom * UNIT_SIZE;
			cw->y = wall->p2.y / cr->zoom * UNIT_SIZE;
			return (wall->index);
		}
		else if (wall->p2.x == cw->x * cr->zoom / UNIT_SIZE && wall->p2.y == cw->y * cr->zoom / UNIT_SIZE && wall->index != prev && \
			(wall->sectors[0] == secid || wall->sectors[1] == secid))
		{
			cw->x = wall->p1.x / cr->zoom * UNIT_SIZE;
			cw->y = wall->p1.y / cr->zoom * UNIT_SIZE;
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
	t_fcoord	cw;
	// t_fcoord	cwold;
	int			curr;


	i = 0;
	tmp = NULL;
	conn = ft_strnew(100);
	iter_wall(cr, 0, -1, &find_any_wall_in_sec);
	// curr = cr->idcurr;
	while (i < cr->sec_num && cr->idcurr != -1)
	{
		ft_putstr_fd(tmp = ft_strjoin("\ns|", ft_ftoa(ST_FLOOR_HIGHT)), fd);
		free(tmp);
		ft_strcpy(line, " ");
    ft_putstr_fd(line, fd);
		ft_putstr_fd(tmp = ft_strjoin(ft_ftoa(ST_CEIL_HIGHT), "|"), fd);
		free(tmp);
		//
		cr->idcurr = -1;
		iter_wall(cr, i, -1, &find_any_wall_in_sec);
		curr = cr->idcurr;
		if (cr->idcurr != -1)
		{
			choose_direction(cr, &cw, find_by_index(cr, cr->idcurr), i);
			// cw.x = (float)find_by_index(cr, cr->idcurr)->p1.x / cr->zoom * UNIT_SIZE;
			// cw.y = (float)find_by_index(cr, cr->idcurr)->p1.y / cr->zoom * UNIT_SIZE;
			// cwold.x = cw.x;
			// cwold.y = cw.y;
			while ((curr = find_next_wall(cr, &cw, curr, i)) >= 0)
			{
				ft_strcpy(line, ft_itoa(find_vt_id(cr, cw.x, cw.y)));
		    	ft_putstr_fd(line, fd);
				printf("CHECKING FOR PORTALS %d\n", curr);
				if (find_by_index(cr, curr)->isportal == 1)
				{
					printf("%d IS PORTAL\n", curr);
					if (find_by_index(cr, curr)->sectors[0] == i)
					{
						printf("SEC No0 IS CURR SEC\n");
						conn = ft_strcat(conn, ft_itoa(find_by_index(cr, curr)->sectors[1]));
					}
					else if (find_by_index(cr, curr)->sectors[1] == i)
					{
						printf("SEC No1 IS CURR SEC\n");
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
					// i++;
					break ;
				}
				else
				{
					ft_strcpy(line, " ");
					conn = ft_strcat(conn, " ");
					ft_putstr_fd(line, fd);
				}
				// cwold.x = cw.x;
				// cwold.y = cw.y;
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

static int			check_vt_dups(t_core *cr, float	x, float y)
{
	int		fd;
	char	*line;

	x = (float)x / cr->zoom * UNIT_SIZE;
	y = (float)y / cr->zoom * UNIT_SIZE;
	fd = open("./maps/testmap", O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_atof(line + 2) == y && \
		ft_atof(line + find_rep_symb(line, ' ', 2) + 1) == x)
			return (1);
		// if (ft_atof(line + 2) == y && \
		// ft_atof(line + find_rep_symb(line, ' ', 2) + 1) == x)
		// 	return (1);
	}
	return (0);
}

static void			record_walls(t_core *cr, char *line, int fd)
{
	t_wall	*wall;

	wall = cr->wlist;
	if (!wall)
		return;
	while (wall)
	{
		if (check_vt_dups(cr, wall->p1.x, wall->p1.y) == 0)
		{
			ft_strcpy(line, "v ");
			ft_putstr_fd(line, fd);
			ft_strcpy(line, ft_ftoa((float)wall->p1.y / cr->zoom * UNIT_SIZE));
			ft_putstr_fd(line, fd);
			ft_strcpy(line, " ");
			ft_putstr_fd(line, fd);
			ft_strcpy(line, ft_ftoa((float)wall->p1.x / cr->zoom * UNIT_SIZE));
			ft_putstr_fd(line, fd);
			ft_strcpy(line, " \n");
			ft_putstr_fd(line, fd);
		}
		if (check_vt_dups(cr, wall->p2.x, wall->p2.y) == 0)
		{
			ft_strcpy(line, "v ");
			ft_putstr_fd(line, fd);
			ft_strcpy(line, ft_ftoa((float)wall->p2.y / cr->zoom * UNIT_SIZE));
			ft_putstr_fd(line, fd);
			ft_strcpy(line, " ");
			ft_putstr_fd(line, fd);
			ft_strcpy(line, ft_ftoa((float)wall->p2.x / cr->zoom * UNIT_SIZE));
			ft_putstr_fd(line, fd);
			ft_strcpy(line, " \n");
			ft_putstr_fd(line, fd);
		}
		wall = wall->next;
	}
}

void            save_map(t_core *cr)
{
  int   fd;
  char  *line;

  	line = (char *)malloc(sizeof(char) * ft_strlen("v 00000 00000") + 1);
	if ((fd = open("./maps/testmap", O_WRONLY | O_CREAT | O_TRUNC, 0777)) < 0)
		printf("ERROR\n");
	record_walls(cr, line, fd);
	record_sectors(cr, line, fd);
	record_objects(cr, fd);
	record_player(cr, fd);
	free(line);
	close(fd);
}
