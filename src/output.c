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

// static void			find_next_wall(t_core *cr, int fd)
// {
// 	t_wall	*wall;
//
// 	wall = cr->wlist;
// 	if (!wall)
// 		return;
//
// }

static void			find_any_wall_in_sec(t_core *cr, t_wall *wall, int refid, int pr2)
{
	(void)pr2;
	if (wall->sectors[0] == refid)
		cr->idcurr = wall->sectors[0];
	else if (wall->sectors[1] == refid)
		cr->idcurr = wall->sectors[1];
}

static void			record_sectors(t_core *cr, char *line, int fd)
{
	t_wall	*wall;
	char		*tmp;
	int			i;

	i = 0;
	wall = cr->wlist;
	if (!wall)
		return;
	ft_strcpy(line, "\n");
	ft_putstr_fd(line, fd);
	while (i < cr->sec_num)
	{
		ft_putstr_fd(tmp = ft_strjoin("s|", ft_itoa(ST_FLOOR_HIGHT)), fd);
		free(tmp);
		ft_strcpy(line, " ");
    ft_putstr_fd(line, fd);
		ft_putstr_fd(tmp = ft_strjoin(ft_itoa(ST_CEIL_HIGHT), "|"), fd);
		free(tmp);
		//
		cr->idcurr = -1;
		iter_wall(cr, -1, -1, &find_any_wall_in_sec);
		// if (cr->idcurr != -1)
		// {
		// 	while (find_next_wall(cr, ))
		//
		// }
		i++;
		wall = wall->next;
	}
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
}
