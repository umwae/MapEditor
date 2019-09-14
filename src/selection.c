/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/14 20:16:58 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int					is_near_wall(t_core *cr, t_wall *wall, int x, int y)
{
	if (x < min(wall->p1.x + cr->offs.x, wall->p2.x + cr->offs.x) - SELECT_PADDING || \
	x > max(wall->p1.x + cr->offs.x, wall->p2.x + cr->offs.x) + SELECT_PADDING || \
	y < min(wall->p1.y + cr->offs.y, wall->p2.y + cr->offs.y) - SELECT_PADDING || \
	y > max(wall->p1.y + cr->offs.y, wall->p2.y + cr->offs.y) + SELECT_PADDING)
		return (0);
	return (1);
}

int					select_wall(t_core *cr, int x, int y)
{
	t_wall		*wall;
	float		dist;
	int			closest_wall;
	float		min_dist;
	float		p;
	float		a;
	float		b;

	min_dist = SELECT_RADIUS;
	wall = cr->wlist;
	if (!wall)
		return (-1);
	while (wall)
	{
		if (is_near_wall(cr, wall, x, y))
			{
				a = calc_dist(x, y, wall->p1.x + cr->offs.x, wall->p1.y + cr->offs.y);
				b = calc_dist(x, y, wall->p2.x + cr->offs.x, wall->p2.y + cr->offs.y);
				p = (a + b + wall->len) / 2;
				dist = 2 * sqrt(p * (p - a) * (p - b) * (p - wall->len)) / wall->len;
				if (dist <= min_dist)
				{
					min_dist = dist;
					closest_wall = wall->index;
				}
			}
			wall = wall->next;
	}
	//
	if (sel_object(cr, x, y) < min_dist)
	{
		obj_info_menu(cr, cr->closest_obj);
		return (-1);
	}
	//
	if (min_dist == SELECT_RADIUS)
	{
		iter_wall(cr, -1, -1, &redraw_color);
		return (-1);
	}
	if (!cr->ctrl_button && !cr->multi_sel)
	{
		if (!cr->multi_sel)
			iter_wall(cr, -1, -1, &redraw_color);
		else
			iter_wall(cr, SELECT_COLOR, -1, &redraw_color);
	}
	return (closest_wall);
}
