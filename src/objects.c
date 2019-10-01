/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/24 21:17:01 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <fcntl.h>

static int		count_obj(t_core *cr)
{
	t_obj	*obj;
	int		i;

	i = 0;
	obj = *cr->olist;
	while (obj)
	{
		obj = obj->next;
		i++;
	}
	return (i);
}

void		add_object(t_core *cr, int x, int y)
{
	t_obj	*obj;


	if (!(obj = (t_obj *)malloc(sizeof(t_obj))))
		err_ex(0);
	obj->next = *cr->olist;
	obj->sec = 0;//Заменить на рейкаст
	obj->fcoord.x = x;
	obj->fcoord.y = y;
	obj->type = DEFAULT_OBJ_TYPE;
	obj->id = count_obj(cr);
	obj->color = OBJECT_COLOR;
	*cr->olist = obj;
}

void		draw_objects_text(t_core *cr)
{
	t_obj		*obj;
	t_coord		xy;
	char		*txt;

	obj = *cr->olist;
	while (obj)
	{
		xy.x = obj->fcoord.x - OBJECT_SIZE / 2 + cr->offs.x;
		xy.y = obj->fcoord.y - OBJECT_SIZE / 2 + cr->offs.y;
		if (!(txt = malloc(sizeof(char) * 5)))
			err_ex(0);
		ft_strcpy(txt, ft_itoa(obj->type));
		mlx_string_put(cr->mlx, cr->win, xy.x, xy.y, 0xffffff, txt);
		free(txt);
		//
		obj = obj->next;
	}
}

void		draw_objects(t_core *cr)
{
	t_obj		*obj;
	t_coord		xy;
	t_coord		ab;

	obj = *cr->olist;
	ab.x = OBJECT_SIZE;
	ab.y = OBJECT_SIZE;
	while (obj)
	{
		xy.x = obj->fcoord.x - OBJECT_SIZE / 2;
		xy.y = obj->fcoord.y - OBJECT_SIZE / 2;
		draw_rectangle_img_pxl(cr, xy, ab, obj->color);
		obj = obj->next;
	}
}

static void	restore_obj_id(t_core *cr)
{
	t_obj		*obj;
	int			i;

	i = 0;
	obj = *cr->olist;
	while (obj)
	{
		obj->id = i;
		i++;
		obj = obj->next;
	}
}

void		del_object(t_core *cr, int idref)
{
	t_obj	*pr;
	t_obj	*obj;

	pr = *cr->olist;
	if (!pr)
		return ;
	if (pr->id == idref)
	{
		*cr->olist = pr->next;
		free(pr);
		cr->closest_obj = NULL;
		restore_obj_id(cr);
		return ;
	}
	while (pr)
	{
		if (!pr->next)
		{
			return ;
		}
		obj = pr->next;
		if (!obj)
			return ;
		if (obj->id == idref)
		{
			pr->next = obj->next;
			free(obj);
			cr->closest_obj = NULL;
			restore_obj_id(cr);
			return ;
		}
		pr = pr->next;
	}
}

void			record_objects(t_core *cr, int fd)
{
	char	*text;
	t_obj	*obj;

	obj = *cr->olist;
	text = ft_strnew(100); //???
	spot_sector_around(cr, obj);
	ft_putstr_fd("\n", fd);
	while (obj)
	{
		// spot_sector_around(cr);
		ft_strcat(text, "o|");
		ft_strcat(text, cr->tms = ft_itoa(obj->sec));
		free(cr->tms);
		ft_strcat(text, "|");
		ft_strcat(text, cr->tms = ft_ftoa(obj->fcoord.x / cr->zoom * UNIT_SIZE));
		free(cr->tms);
		ft_strcat(text, " ");
		ft_strcat(text, cr->tms = ft_ftoa(obj->fcoord.y / cr->zoom * UNIT_SIZE));
		free(cr->tms);
		ft_strcat(text, "|");
		ft_strcat(text, cr->tms = ft_itoa(obj->type));
		free(cr->tms);
		// ft_strcat(text, "|");
		// ft_strcat(text, ft_itoa(cr->player.angle));
		ft_strcat(text, "|\n");
		ft_putstr_fd(text, fd);
		obj = obj->next;
		ft_strclr(text);
	}
	free(text);
}

void			load_objects(t_core *cr)
{
	char		**oarr;
	int			fd;
	t_obj		*obj;
	char		*line = NULL;

	fd = open("./maps/testmap", O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'o')
		{
			oarr = ft_strsplit(line, '|');
			if (!(obj = (t_obj *)malloc(sizeof(t_obj))))
				err_ex(0);
			obj->sec = ft_atoi(oarr[1]);
			obj->fcoord.x = ft_atof(oarr[2]) * cr->zoom / UNIT_SIZE;
			obj->fcoord.y = ft_atof(ft_strchr(oarr[2], ' ') + 1) * cr->zoom / UNIT_SIZE;
			obj->type = ft_atoi(oarr[3]);
			obj->id = count_obj(cr);
			obj->color = OBJECT_COLOR;
			obj->next = *cr->olist;
			*cr->olist = obj;
			ft_arrfree(&oarr, ft_arrlen(oarr));
		}
		free(line);
	}
	free(line);
	close(fd);
	// ft_arrfree(&oarr, 4);
	return ;
}

static void		restore_obj_color(t_core *cr)
{
	t_obj	*obj;

	obj = *cr->olist;
	while (obj)
	{
		obj->color = OBJECT_COLOR;
		obj = obj->next;
	}
}

float			sel_object(t_core *cr, int x, int y)
{
	t_obj	*obj;
	float	min_dist;
	float	res;

	min_dist = SELECT_RADIUS;
	obj = *cr->olist;
	restore_obj_color(cr);
	while (obj)
	{
		if ((res = calc_dist(x, y, obj->fcoord.x + cr->offs.x, obj->fcoord.y + cr->offs.y)) < min_dist)
		{
			cr->closest_obj = obj;
			min_dist = res;
		}
		obj = obj->next;
	}
	return (min_dist);
}
