/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/06 22:12:20 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

static float		calc_dist(int x0, int y0, int x1, int y1)
{
	int	dx;
	int	dy;

	dx = abs(x0) > abs(x1) ? x0 - x1 : x1 - x0;
	dy = abs(y0) > abs(y1) ? y0 - y1 : y1 - y0;
	return (sqrt(pow(dx, 2) + pow(dy, 2)));
}

void					magnet(t_core *cr, int *x, int *y)//How do they work???
{
	t_wall	*wall;
	float		dist;
	int			closest_x;
	int			closest_y;
	float		min_dist;

	closest_x = *x;
	closest_y = *y;
	min_dist = MAGNET_RADIUS;
	wall = cr->sectors->walls;
	if (!wall)
		return ;
	while (wall)
	{
		if ((dist = calc_dist(*x, *y, wall->p1.x, wall->p1.y)) <= min_dist)
		{
			min_dist = dist;
			closest_x = wall->p1.x;
			closest_y = wall->p1.y;
		}
		if ((dist = calc_dist(*x, *y, wall->p2.x, wall->p2.y)) <= min_dist)
		{
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

void					add_wall(t_core *cr, t_sector *sec)
{
	t_wall	*wall;
	t_wall	*tmp;

	wall = sec->walls;
	if (!wall)
	{
		cr->sectors->walls = (t_wall *)malloc(sizeof(t_wall));
		cr->sectors->walls->next = NULL;
		wall = sec->walls;
	}
	else
	{
		while (wall->next)
			wall = wall->next;
		wall->next = (t_wall *)malloc(sizeof(t_wall));
		wall = wall->next;
		wall->next = NULL;
	}
	wall->p1.x = cr->vs.mem_x;
	wall->p1.y = cr->vs.mem_y;
	wall->p2.x = cr->vs.x1;
	wall->p2.y = cr->vs.y1;
}
