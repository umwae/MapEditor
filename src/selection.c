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

int					is_near_wall(t_wall *wall, int x, int y)
{
	if (x < min(wall->p1.x, wall->p2.x) - SELECT_PADDING || \
	x > max(wall->p1.x, wall->p2.x) + SELECT_PADDING || \
	y < min(wall->p1.y, wall->p2.y) - SELECT_PADDING || \
	y > max(wall->p1.y, wall->p2.y) + SELECT_PADDING)
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
		if (is_near_wall(wall, x, y))
			{
				a = calc_dist(x, y, wall->p1.x, wall->p1.y);
				b = calc_dist(x, y, wall->p2.x, wall->p2.y);
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
	if (min_dist == SELECT_RADIUS)
		return (-1);
	iter_wall(cr, APP_SEC_COLOR, -1, &reset_color_exc);
	return (closest_wall);
}
