/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/19 21:06:10 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdio.h"
#include <fcntl.h>
#include "stdlib.h"
#include "math.h"

static void			find_any_wall_in_sec(t_core *cr, t_wall *wall, int refid, int pr2)
{
	(void)pr2;
	if (wall->sectors[0].s == refid)
		cr->idcurr = wall->index;
	else if (wall->sectors[1].s == refid)
		cr->idcurr = wall->index;
}

void			record_sectors(t_core *cr, int fd)
{
	char		*txt;
	char		*tmp;
	char		*conn;
	char		*wtx;
	int			doprint_wtx = 0;
	t_wall		*wtmp;
	int			i;
	t_fcoord	cw;
	int			curr;
	t_sec		*sec;

	i = 0;
	txt = ft_strnew(300);
	conn = ft_strnew(300);
	wtx = ft_strnew(3000);
	iter_wall(cr, 0, -1, &find_any_wall_in_sec);
	while (i < cr->sec_num && cr->idcurr != -1)
	{
		sec = find_sec_list(cr, i);
		ft_strcat(txt, "\ns|");
		ft_strcat(txt, (tmp = ft_ftoa(sec->floor)));
		free(tmp);
		ft_strcat(txt, " ");
		ft_strcat(txt, (tmp = ft_ftoa(sec->ceiling)));
		free(tmp);
		ft_strcat(txt, "|");
		//
		ft_strcat(wtx, "\nt|");
		ft_strcat(wtx, (tmp = ft_itoa(i)));
		free(tmp);
		ft_strcat(wtx, "|");
		ft_strcat(wtx, (tmp = ft_itoa(find_sec_list(cr, i)->ftex)));
		free(tmp);
		ft_strcat(wtx, " ");
		ft_strcat(wtx, (tmp = ft_itoa(find_sec_list(cr, i)->ctex)));
		free(tmp);
		ft_strcat(wtx, "|");
		//
		cr->idcurr = -1;
		iter_wall(cr, i, -1, &find_any_wall_in_sec);
		curr = cr->idcurr;
		if (cr->idcurr != -1)
		{
			choose_direction(cr, &cw, find_by_index(cr, cr->idcurr), i);
			while ((curr = find_next_wall(cr, &cw, curr, i)) >= 0)
			{
				wtmp = find_by_index(cr, curr);
				//
				ft_strcat(txt, (tmp = ft_itoa(find_vt_id(cr, cw.x, cw.y))));
				//
				if (wtmp->sectors[0].t != -1 || wtmp->sectors[1].t != -1 || sec->floor != ST_FLOOR_HIGHT || sec->ceiling != ST_CEIL_HIGHT || \
				sec->illum != ST_ILLUMINATION || sec->ftex != ST_FTEX || sec->ftex != ST_CTEX)
					doprint_wtx = 1;
				ft_strcat(wtx, cr->tms = ft_itoa(wtmp->sectors[0].s == i ? wtmp->sectors[0].t : wtmp->sectors[1].t));
				free(cr->tms);
				//
				free(tmp);
				if (wtmp->isportal == 1)
				{
					if (wtmp->sectors[0].s == i)
					{
						conn = ft_strcat(conn, (tmp = ft_itoa(wtmp->sectors[1].s)));
						free(tmp);
					}
					else if (wtmp->sectors[1].s == i)
					{
						conn = ft_strcat(conn, (tmp = ft_itoa(wtmp->sectors[0].s)));
						free(tmp);
					}
				}
				else
				{
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
					ft_strcat(txt, " ");
					ft_strcat(conn, " ");
					ft_strcat(wtx, " ");
				}
			}
		}
		ft_strcat(txt, "|");
		ft_putstr_fd(txt, fd);
		if (sec->illum > 0)
		{
			ft_strcat(conn, "|");
			ft_strcat(conn, (tmp = ft_ftoa(sec->illum)));
			free(tmp);
			ft_strcat(conn, "|");
		}
		ft_putstr_fd(conn, fd);
		ft_strclr(txt);
		ft_strclr(conn);
		//
		ft_strcat(wtx, "|");
		i++;
	}
		free(txt);
		free(conn);
		ft_putstr_fd("\n", fd);
		//
		if (i == cr->sec_num)
		{
			ft_putstr_fd(wtx, fd);
			ft_putstr_fd("\n", fd);
		}
		free(wtx);
}

int				check_vt_dups(t_core *cr, float	x, float y)
{
	int		fd;
	char	*line;

	if ((fd = open("./maps/testmap", O_RDONLY)) == -1)
      reopen_10_times(&fd);
	prepare_gnlstr(&cr->gnlstr[6]);
	while (gnl_struct(&cr->gnlstr[6], fd, &line) > 0)
	{
		if ((int)(ft_atof(line + 2) * cr->zoom / UNIT_SIZE) == y && \
		(int)(ft_atof(line + find_rep_symb(line, ' ', 2) + 1) * cr->zoom / UNIT_SIZE) == x)
		{
			free(line);
			close(fd);
			return (1);
		}
		free(line);
	}
	free(line);
	close(fd);
	return (0);
}
