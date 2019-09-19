/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/19 19:51:07 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <fcntl.h>

void		name_sec_list(t_core *cr)
{
	t_sec		*sec;

	sec = *cr->slist;
	while (sec)
	{
		printf("%d ", sec->id);
		sec = sec->next;
	}
	printf("\n");
}

void		add_sec_list(t_core *cr)
{
	t_sec	*sec;

	sec = (t_sec *)malloc(sizeof(t_sec));
	sec->next = *cr->slist;
	sec->illum = ST_ILLUMINATION;
	sec->floor = ST_FLOOR_HIGHT;
	sec->ceiling = ST_CEIL_HIGHT;
	sec->ftex = -1;
	sec->ctex = -1;
	sec->id = cr->sec_num - 1;
	sec->isdoor = 0;
	sec->isfinish = 0;
	*cr->slist = sec;
}

void				sec_list_id_replace(t_core *cr, int new, int old)
{
	t_sec		*sec;

	sec = *cr->slist;
	while (sec->next)
	{
		if (sec->id == old)
		{
			sec->id = new;
			return ;
		}
		sec = sec->next;
	}
}

void		del_sec_list(t_core *cr, int idref)
{
	t_sec	*pr;
	t_sec	*sec;

	pr = *cr->slist;
	if (!pr)
		return ;
	if (pr->id == idref)
	{
		*cr->slist = pr->next;
		free(pr);
		return ;
	}
	while (pr)
	{
		if (!pr->next)
		{
			return ;
		}
		sec = pr->next;
		if (!sec)
			return ;
		if (sec->id == idref)
		{
			pr->next = sec->next;
			free(sec);
			return ;
		}
		pr = pr->next;
	}
}

t_sec				*find_sec_list(t_core *cr, int idref)
{
	t_sec		*sec;

	sec = *cr->slist;
	while (sec)
	{
		if (sec->id == idref)
			break ;
		sec = sec->next;
	}
	return (sec);
}

void					print_sec_num(t_core *cr)
{
	t_wall		*wall;
	int			am;
	int			i;
	t_coord		summ;
	char 		*txt;

	txt = ft_strnew(10);
	i = 0;
	while (i < cr->sec_num)
	{
		am = 0;
		summ.x = 0;
		summ.y = 0;
		wall = cr->wlist;
		while (wall)
		{
			if (wall->sectors[0].s == i || wall->sectors[1].s == i)
			{
				am += 2;
				summ.x += (wall->p1.x + wall->p2.x);
				summ.y += (wall->p1.y + wall->p2.y);
			}
			wall = wall->next;
		}
		summ.x = (float)summ.x / am;
		summ.y = (float)summ.y / am;
		// ft_strcat(txt, "[");
		ft_strcat(txt, ft_itoa(i));
		// ft_strcat(txt, "]");
		mlx_string_put(cr->mlx, cr->win, summ.x + cr->offs.x, \
		summ.y + cr->offs.y, 0x00ffb5, txt);
		ft_strclr(txt);
		i++;
	}
}

void		load_sec_info(t_core *cr)
{
	int		fd;
	char 	*line;
	t_sec	*sec;
	char  	**pts;
	int		i;

	i = 0;
	fd = open("./maps/testmap", O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 't')
		{
			pts = ft_strsplit(line, '|');
			sec = find_sec_list(cr, ft_atoi(pts[1]));
			sec->ftex = ft_atoi(pts[2]);
			if (ft_strncmp(ft_strchr(pts[2], ' '), "sky", 3) == 0)
				sec->ctex = SKY;
			else
				sec->ctex = ft_atoi(ft_strchr(pts[2], ' '));
		}
		free(line);
	}
	free(line);
	close(fd);
}
