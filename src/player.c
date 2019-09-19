/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/19 20:14:40 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <fcntl.h>

static void	calc(t_core *cr, t_wall *wall, t_coord ray, t_obj *obj)
{
	float	m1;
	float	m2;
	float b1;
	float b2;
	float dist = cr->dist;



	//если первый отрезок вертикальный
	if (wall->p1.x - wall->p2.x == 0)
	{
		if (obj->fcoord.y > min(wall->p1.y, wall->p2.y) && \
		obj->fcoord.y < max(wall->p1.y, wall->p2.y) && \
		((ray.x > obj->fcoord.x && obj->fcoord.x <= wall->p1.x) || \
		(ray.x < obj->fcoord.x && obj->fcoord.x >= wall->p1.x)))
		{
			cr->hit.x = wall->p1.x;
			cr->hit.y = obj->fcoord.y;
			dist = cr->hit.x > obj->fcoord.x ? cr->hit.x - obj->fcoord.x : obj->fcoord.x - cr->hit.x;
			if (dist < cr->dist)
			{
				cr->dist = dist;
				cr->secmem[0] = wall->sectors[0].s;
				cr->secmem[1] = wall->sectors[1].s;
				cr->debug = cr->hit;
			}
		}
		return ;
	}
	m1 = (float)(wall->p1.y - wall->p2.y) / (wall->p1.x - wall->p2.x != 0 ? wall->p1.x - wall->p2.x : 0.01);
	m2 = (float)(ray.y - obj->fcoord.y) / (ray.x - obj->fcoord.x != 0 ? ray.x - obj->fcoord.x : 0.01);
	b1 = wall->p1.y - m1 * wall->p1.x;
	b2 = ray.y - m2 * ray.x;
	if (m1 == m2)
    return ;
	cr->hit.x = (b2 - b1) / (m1 - m2);
	if (cr->hit.x < min(wall->p1.x, wall->p2.x) || cr->hit.x > max(wall->p1.x, wall->p2.x))
		return ;
	if ((cr->hit.x - obj->fcoord.x < 0 && cr->dir.x > 0) || (cr->hit.x - obj->fcoord.x > 0 && cr->dir.x< 0))
		return ;
	cr->hit.y = wall->p1.y + (cr->hit.x - wall->p1.x) * m1;
	dist = sqrt(pow(cr->hit.x - obj->fcoord.x, 2) + pow(cr->hit.y - obj->fcoord.y, 2));
	if (dist < cr->dist)
	{
		cr->dist = dist;
		cr->secmem[0] = wall->sectors[0].s;
		cr->secmem[1] = wall->sectors[1].s;
		cr->debug = cr->hit;
	}
}

static void	raycast(t_core *cr, t_obj *obj)
{
	t_wall		*wall;
	t_coord		ray;

	cr->dist = 1000;
	ray.x = obj->fcoord.x + cr->dir.x;
	ray.y = obj->fcoord.y + cr->dir.y;
	wall = cr->wlist;
	while (wall)
	{
		calc(cr, wall, ray, obj);
		wall = wall->next;
	}
	if (cr->secmem[0] != -1 || cr->secmem[1] != -1)
	{
		cr->vs.x0 = obj->fcoord.x + cr->offs.x;
		cr->vs.y0 = obj->fcoord.y + cr->offs.y;
		cr->vs.x1 = cr->debug.x + cr->offs.x;
		cr->vs.y1 = cr->debug.y + cr->offs.y;
		cr->vs.color = 0xff0000;
		bresenham(cr, &pxl_put_wrap);
	}
}

void			draw_player(t_core *cr)
{
	t_coord		xy;
	t_coord		ab;

	ab.x = PLAYER_SIZE;
	ab.y = PLAYER_SIZE;
	xy.x = cr->player.fcoord.x - PLAYER_SIZE / 2 + cr->offs.x;
	xy.y = cr->player.fcoord.y - PLAYER_SIZE / 2 + cr->offs.y;
	draw_rectangle(cr, xy, ab, PLAYER_COLOR);
}

void			spot_sector_around(t_core *cr, t_obj *obj)
{
	int			mem[2];

	if (!obj)
		return ;
	cr->secmem[0] = -1;
	cr->secmem[1] = -1;
	mem[0] = -1;
	mem[1] = -1;
	cr->dir.x = 10;
	cr->dir.y = 0;
	raycast(cr, obj);
	mem[0] = cr->secmem[0];
	mem[1] = cr->secmem[1];
	cr->dir.x = -10;
	cr->dir.y = 0;
	raycast(cr, obj);
	if ((mem[0] == cr->secmem[0] || mem[0] == cr->secmem[1]) && mem[0] != -1)
		obj->sec = mem[0];
	else if ((mem[1] == cr->secmem[0] || mem[1] == cr->secmem[1]) && mem[1] != -1)
		obj->sec = mem[1];

}
void			record_player(t_core *cr, int fd)
{
	char	*text;

	ft_putstr_fd("\n", fd);
	text = ft_strnew(ft_strlen("p|0.0 0.0|0|0.0|") + 1);
	spot_sector_around(cr, &cr->player);
	ft_strcat(text, "p|");
	ft_strcat(text, ft_ftoa(cr->player.fcoord.y / cr->zoom * UNIT_SIZE));
	ft_strcat(text, " ");
	ft_strcat(text, ft_ftoa(cr->player.fcoord.x / cr->zoom * UNIT_SIZE));
	ft_strcat(text, "|");
	ft_strcat(text, ft_itoa(cr->player.sec));
	ft_strcat(text, "|");
	ft_strcat(text, ft_itoa(cr->player.angle));
	ft_strcat(text, "|\n");
	ft_putstr_fd(text, fd);
}

void			load_player(t_core *cr, char **line)
{
	char		**parr;
	int			fd;

	fd = open("./maps/testmap", O_RDONLY);
	while (get_next_line(fd, line) > 0)
	{
		if (*line[0] == 'p')
		{
			parr = ft_strsplit(*line, '|');
			cr->player.fcoord.y = ft_atof(parr[1]) * cr->zoom / UNIT_SIZE;
			cr->player.fcoord.x = ft_atof(ft_strchr(parr[1], ' ') + 1) * cr->zoom / UNIT_SIZE;
			cr->player.sec = ft_atoi(parr[2]);
			cr->player.angle = ft_atof(parr[3]);
			close(fd);
			return ;
		}
	}
	close(fd);
	return ;
}
