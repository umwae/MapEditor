/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/09 20:20:21 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

static void	calc(t_core *cr, t_wall *wall, t_coord ray)
{
	float	m1;
	float	m2;
	float b1;
	float b2;
	float dist = cr->dist;



	//если первый отрезок вертикальный
	if (wall->p1.x - wall->p2.x == 0)
	{
		if (cr->player.coord.y > min(wall->p1.y, wall->p2.y) && \
		cr->player.coord.y < max(wall->p1.y, wall->p2.y) && \
		((ray.x > cr->player.coord.x && cr->player.coord.x <= wall->p1.x) || \
		(ray.x < cr->player.coord.x && cr->player.coord.x >= wall->p1.x)))
		{
			cr->hit.x = wall->p1.x;
			cr->hit.y = cr->player.coord.y;
			dist = cr->hit.x > cr->player.coord.x ? cr->hit.x - cr->player.coord.x : cr->player.coord.x - cr->hit.x;
			if (dist < cr->dist)
			{
				cr->dist = dist;
				cr->secmem[0] = wall->sectors[0];
				cr->secmem[1] = wall->sectors[1];
				cr->debug = cr->hit;
			}
		}
		return ;
	}
	m1 = (float)(wall->p1.y - wall->p2.y) / (wall->p1.x - wall->p2.x != 0 ? wall->p1.x - wall->p2.x : 0.01);
	m2 = (float)(ray.y - cr->player.coord.y) / (ray.x - cr->player.coord.x != 0 ? ray.x - cr->player.coord.x : 0.01);
	b1 = wall->p1.y - m1 * wall->p1.x;
	b2 = ray.y - m2 * ray.x;
	if (m1 == m2)
    return ;
	cr->hit.x = (b2 - b1) / (m1 - m2);
	if (cr->hit.x < min(wall->p1.x, wall->p2.x) || cr->hit.x > max(wall->p1.x, wall->p2.x))
		return ;
	if ((cr->hit.x - cr->player.coord.x < 0 && cr->dir.x > 0) || (cr->hit.x - cr->player.coord.x > 0 && cr->dir.x< 0))
		return ;
	cr->hit.y = wall->p1.y + (cr->hit.x - wall->p1.x) * m1;
	dist = sqrt(pow(cr->hit.x - cr->player.coord.x, 2) + pow(cr->hit.y - cr->player.coord.y, 2));
	if (dist < cr->dist)
	{
		cr->dist = dist;
		cr->secmem[0] = wall->sectors[0];
		cr->secmem[1] = wall->sectors[1];
		cr->debug = cr->hit;
	}
}

static void	raycast(t_core *cr)
{
	t_wall		*wall;
	t_coord		ray;

	cr->dist = 1000;
	ray.x = cr->player.coord.x + cr->dir.x;
	ray.y = cr->player.coord.y + cr->dir.y;
	wall = cr->wlist;
	while (wall)
	{
		calc(cr, wall, ray);
		wall = wall->next;
	}
	if (cr->secmem[0] != -1 || cr->secmem[1] != -1)
	{
		cr->vs.x0 = cr->player.coord.x + cr->offs.x;
		cr->vs.y0 = cr->player.coord.y + cr->offs.y;
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

	ab.x = OBJECT_SIZE;
	ab.y = OBJECT_SIZE;
	xy.x = cr->player.coord.x - OBJECT_SIZE / 2 + cr->offs.x;
	xy.y = cr->player.coord.y - OBJECT_SIZE / 2 + cr->offs.y;
	draw_rectangle(cr, xy, ab, PLAYER_COLOR);
}

void			spot_sector_around(t_core *cr)
{
	int			mem[2];

	cr->secmem[0] = -1;
	cr->secmem[1] = -1;
	mem[0] = -1;
	mem[1] = -1;
	cr->dir.x = 10;
	cr->dir.y = 0;
	raycast(cr);
	mem[0] = cr->secmem[0];
	mem[1] = cr->secmem[1];
	cr->dir.x = -10;
	cr->dir.y = 0;
	raycast(cr);
	if ((mem[0] == cr->secmem[0] || mem[0] == cr->secmem[1]) && mem[0] != -1)
		cr->player.sec = mem[0];
	else if ((mem[1] == cr->secmem[0] || mem[1] == cr->secmem[1]) && mem[1] != -1)
		cr->player.sec = mem[1];

}
void			record_player(t_core *cr, int fd)
{
	char	*text;

	ft_putstr_fd("\n", fd);
	text = ft_strnew(ft_strlen("p|0.0 0.0|0|0.0|") + 1);
	spot_sector_around(cr);
	ft_strcat(text, "p|");
	ft_strcat(text, ft_ftoa(cr->player.coord.y / cr->zoom * UNIT_SIZE));
	ft_strcat(text, " ");
	ft_strcat(text, ft_ftoa(cr->player.coord.x / cr->zoom * UNIT_SIZE));
	ft_strcat(text, "|");
	ft_strcat(text, ft_itoa(cr->player.sec));
	ft_strcat(text, "|");
	ft_strcat(text, ft_itoa(cr->player.angle));
	ft_strcat(text, "|\n");
	ft_putstr_fd(text, fd);
}
