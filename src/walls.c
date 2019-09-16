/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/16 20:37:06 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

t_wall			*get_last_wall(t_core *cr)
{
	t_wall		*wall;

	wall = cr->wlist;
	while (wall->next)
		wall = wall->next;
	return (wall);
}

void			iter_wall(t_core *cr, int pr1, int pr2, void (*f)(t_core *, t_wall *, int, int))//Переписать на void* типы
{
		t_wall		*wall;

		wall = cr->wlist;
		if (!wall)
			return ;
		while (wall)
		{
			(*f)(cr, wall, pr1, pr2);
			wall = wall->next;
		}
}

t_wall				*find_by_index(t_core *cr, int index)
{
	t_wall		*wall;

	wall = cr->wlist;
	while (wall && index--)
		wall = wall->next;
	return (wall);
}

void					magnet(t_core *cr, int *x, int *y, int check_start)//How do they work???
{
	t_wall		*wall;
	float		dist;
	int			closest_x;
	int			closest_y;
	float		min_dist;

	closest_x = *x;
	closest_y = *y;
	min_dist = MAGNET_RADIUS;
	wall = cr->wlist;
	if (!wall)
		return ;
	while (wall)
	{
		if ((dist = calc_dist(*x + cr->offs.x, *y + cr->offs.y, wall->p1.x + cr->offs.x * 2, wall->p1.y + cr->offs.y * 2)) <= min_dist)
		{
			if (((wall->p1.x + cr->offs.x == cr->vs.mem_x && wall->p1.y + cr->offs.y == cr->vs.mem_y) || \
			(wall->p2.x + cr->offs.x == cr->vs.mem_x && wall->p2.y + cr->offs.y == cr->vs.mem_y)) && check_start == 1)
				return ;
			min_dist = dist;
			closest_x = wall->p1.x;
			closest_y = wall->p1.y;
		}
		if ((dist = calc_dist(*x + cr->offs.x, *y + cr->offs.y, wall->p2.x + cr->offs.x * 2, wall->p2.y + cr->offs.y * 2)) <= min_dist)
		{
			if (((wall->p1.x + cr->offs.x == cr->vs.mem_x && wall->p1.y + cr->offs.y == cr->vs.mem_y) || \
			(wall->p2.x + cr->offs.x  == cr->vs.mem_x && wall->p2.y + cr->offs.y == cr->vs.mem_y)) && check_start == 1)
				return ;
			min_dist = dist;
			closest_x = wall->p2.x;
			closest_y = wall->p2.y;
		}
		wall = wall->next;
	}
	if (min_dist == MAGNET_RADIUS)
		return ;
	*x = closest_x + cr->offs.x;
	*y = closest_y + cr->offs.y;
}

void					add_wall(t_core *cr)
{
	t_wall	*wall;
	int			i;

	if (cr->vs.x1 == cr->vs.mem_x && cr->vs.y1 == cr->vs.mem_y)
		return ;
	i = 1;
	wall = cr->wlist;
	if (!wall)
	{
		cr->wlist = (t_wall *)malloc(sizeof(t_wall));
		wall = cr->wlist;
		cr->wlist->next = NULL;
		i = 0;
	}
	else
	{
		while (wall->next)
		{
			wall = wall->next;
			i++;
		}
		wall->next = (t_wall *)malloc(sizeof(t_wall));
		wall = wall->next;
		wall->next = NULL;
	}
	wall->p1.x = cr->vs.mem_x;
	wall->p1.y = cr->vs.mem_y;
	wall->p2.x = cr->vs.x1;
	wall->p2.y = cr->vs.y1;
	wall->color = WALL_COLOR;
	wall->index = i;
	wall->len = calc_dist(wall->p1.x, wall->p1.y, wall->p2.x, wall->p2.y);
	wall->sectors[0].s = -1;
	wall->sectors[1].s = -1;
	wall->sectors[0].t = 0;
	wall->sectors[1].t = 2;
	wall->isportal = cr->mpsw;
	cr->mpsw = 0;
	printf("w>>>%d %d\n", wall->sectors[0].t, wall->sectors[1].t);
	iter_wall(cr, 0, 0, &redraw_color);
}
