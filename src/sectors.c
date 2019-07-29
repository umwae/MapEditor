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

// void				smallest_angle(t_core *cr, t_coord links**)
// {
//
// }

void				halfplane(t_core *cr, t_wall *ref)
{
	float		d;
	t_wall	*wall;

	wall = cr->wlist;
	if (!wall || !ref)
		return ;
	while (d == d)
	{
		while (wall)
		{
			if (wall->index != ref->index)
			{
				if ((wall->p1.x == ref->p1.x) && (wall->p1.y == ref->p1.y))
				{
					d = (wall->p2.x - ref->p1.x) * (ref->p2.y - ref->p1.y) - (wall->p2.y - ref->p1.y) * (wall->p2.x - ref->p1.x);
					printf("%f\n", d);
					wall->color = 0xff0000;
					// ref = wall;
					// wall = cr->wlist;
				}
				else if ((wall->p2.x == ref->p1.x) && (wall->p2.y == ref->p1.y))
				{
					d = -(wall->p1.x - ref->p1.x) * (ref->p2.y - ref->p2.y) - (wall->p1.y - ref->p1.y) * (wall->p1.x - ref->p1.x);
					printf("%f\n", d);
					wall->color = 0xff0000;
					// ref = wall;
					// wall = cr->wlist;
				}
			}
			wall = wall->next;
		}
		return ;
	}
}
