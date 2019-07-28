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
#include "stdlib.h"
#include "math.h"

t_wall				*find_by_index(t_core *cr, int index)
{
	t_wall		*wall;

	wall = cr->wlist;
	// if (!wall || index < 0)
	// 	return (NULL);
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
		if ((dist = calc_dist(*x, *y, wall->p1.x, wall->p1.y)) <= min_dist)
		{
			if (((wall->p1.x == cr->vs.mem_x && wall->p1.y == cr->vs.mem_y) || \
			(wall->p2.x == cr->vs.mem_x && wall->p2.y == cr->vs.mem_y)) && check_start == 1)
				return ;
			min_dist = dist;
			closest_x = wall->p1.x;
			closest_y = wall->p1.y;
		}
		if ((dist = calc_dist(*x, *y, wall->p2.x, wall->p2.y)) <= min_dist)
		{
			if (((wall->p1.x == cr->vs.mem_x && wall->p1.y == cr->vs.mem_y) || \
			(wall->p2.x == cr->vs.mem_x && wall->p2.y == cr->vs.mem_y)) && check_start == 1)
				return ;
			min_dist = dist;
			closest_x = wall->p2.x;
			closest_y = wall->p2.y;
		}
		wall = wall->next;
	}
	if (min_dist == MAGNET_RADIUS)
		return ;
	*x = closest_x;
	*y = closest_y;
}

void					add_wall(t_core *cr)
{
	t_wall	*wall;
	int			i;

	i = 1;
	wall = cr->wlist;
	if (!wall)
	{
		cr->wlist = (t_wall *)malloc(sizeof(t_wall));
		cr->wlist->next = NULL;
		wall = cr->wlist;
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
}
