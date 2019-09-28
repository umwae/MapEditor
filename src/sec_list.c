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

	printf("ADD SEC %d\n", cr->sec_num - 1);
	sec = (t_sec *)malloc(sizeof(t_sec));
	sec->next = *cr->slist;
	sec->illum = ST_ILLUMINATION;
	sec->floor = ST_FLOOR_HIGHT;
	sec->ceiling = ST_CEIL_HIGHT;
	sec->ftex = ST_FTEX;
	sec->ctex = ST_CTEX;
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
	printf("SECDEL IDREF %d\n", idref);
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

static void	set_textures(t_core *cr, t_wall *wall, int texture, int secid)
{
	if (wall->index != cr->idcurr)
		return ;
	if (wall->sectors[0].s == secid)
		wall->sectors[0].t = texture;
	else if (wall->sectors[1].s == secid)
		wall->sectors[1].t = texture;
}

// static void	find_wall_by_xy(t_core *cr, t_wall *wall, int y, int x)
// {
// 	if ((wall->p1.y == y && wall->p1.x == x) || (wall->p2.y == y && wall->p2.x == x))
// 		cr->idcurr = wall->index;
// }

static void      find_wall_by_xy(t_core *cr, t_coord inp1, t_coord inp2)
{
  t_wall  *wall;

  wall = cr->wlist;
//   if (!wall)
//     return (0);
  while (wall)
  {
    if (((inp1.x == wall->p1.x && inp1.y == wall->p1.y) && (inp2.x == wall->p2.x && inp2.y == wall->p2.y)) || \
    ((inp1.x == wall->p2.x && inp1.y == wall->p2.y) && (inp2.x == wall->p1.x && inp2.y == wall->p1.y)))
	{
		cr->idcurr = wall->index;
		return ;
	}
    wall = wall->next;
  }
}

static int			find_w_id(t_core *cr)
{
	int		fd;
	char	*line;
	int		i;
	t_coord	xy1;
	t_coord	xy2;

	// printf("looking for v id: %f %f\n", x, y);
	fd = open(SAVEPATH, O_RDONLY);
	i = -1;
	while (i < cr->vt[0])
	{
		get_next_line(fd, &line);
		if (line[0] != 'v')
			return (0);
		i++;
	}
	xy1.y = ft_atof(line + 2) * cr->zoom / UNIT_SIZE;
	xy1.x = ft_atof(line + find_rep_symb(line, ' ', 2) + 1) * cr->zoom / UNIT_SIZE;
//Переоткрыть
	fd = open(SAVEPATH, O_RDONLY);
	i = -1;
	while (i < cr->vt[1])
	{
		get_next_line(fd, &line);
		if (line[0] != 'v')
			return (0);
		i++;
	}
	xy2.y = ft_atof(line + 2) * cr->zoom / UNIT_SIZE;
	xy2.x = ft_atof(line + find_rep_symb(line, ' ', 2) + 1) * cr->zoom / UNIT_SIZE;
	find_wall_by_xy(cr, xy1, xy2);
	return (cr->idcurr);
}

static char			**find_sec_in_save(t_core *cr, int secid)
{
	int		fd;
	char 	*line;
	char	**pts;
	char	**tmp;
	int		i;

	i = -1;
	if (!(fd = open(SAVEPATH, O_RDONLY)))
		printf("FD ERR %d\n", secid);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 's')
		{
			i++;
			if (i == secid)
			{
				// line = ft_strjoin(line, " ");
	  			// line = ft_strjoin(line, ft_strsub(line, find_rep_symb(line, '|', 2) + 1, \
	  			// find_rep_symb(line, '|', 3) - (find_rep_symb(line, '|', 2) + 1)));
				
				tmp = ft_strsplit(line, '|');

				printf("*777 %s\n", tmp[2]);
				// tmp[2] = ft_strjoin(tmp[2], " ");
	  			// tmp[2] = ft_strjoin(tmp[2], ft_strsub(tmp[2], 0, \
	  			// ft_strlen(tmp[2]) - ((ft_strrchr(tmp[2], ' ') - tmp[2]))));
				
				tmp[2] = ft_strjoin(" ", tmp[2]);
				tmp[2] = ft_strjoin(ft_strrchr(tmp[2], ' '), tmp[2]);

				printf("*888 %s\n", tmp[2]);
				pts = ft_strsplit(tmp[2], ' ');
				ft_arrfree(&tmp, ft_arrlen(tmp));
				return (pts);
			}
		}
	}
	return (NULL);
}

static void	load_textures(t_core *cr, char *str, int secid)
{
	char	**pts;
	char	**sts;
	int		i;
	int		texture;

	i = 0;
	pts = ft_strsplit(str, ' ');
	if (!(sts = find_sec_in_save(cr, secid)))
		printf("STS ERR SEC ID %d\n", secid);
	while (pts[i])
	{
		cr->vt[0] = ft_atoi(sts[i]);
		cr->vt[1] = ft_atoi(sts[i + 1]);
		find_w_id(cr);
		iter_wall(cr, ft_atoi(pts[i]), secid, &set_textures);
		i++;
	}
	ft_arrfree(&sts, i);
	ft_arrfree(&pts, ft_arrlen(pts));
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
			load_textures(cr, pts[3], ft_atoi(pts[1]));
		}
		free(line);
	}
	free(line);
	close(fd);
}
