/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/31 19:32:22 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
//atq2
static void				calc_angle(t_core *cr, t_wall *ref)
{
	float	c;
	float	b;
	float	a;
	float	ang;
	int		i;
	float	ang_mem;
	int		id;

	i = 0;
	ang_mem = PI_CEIL;
	c = ref->len;
	// printf("%d\n", cr->links[i]->x);
	while (cr->links[i])
	{
		b = calc_dist(ref->p1.x, ref->p1.y, cr->links[i]->p.x, cr->links[i]->p.y);
		a = calc_dist(ref->p2.x, ref->p2.y, cr->links[i]->p.x, cr->links[i]->p.y);
		ang = acos((b * b + c * c - a * a) / (2 * b * c));
		printf("ANGLE: %f %f|%f|%f\n", ang, a, b, c);
		fflush(stdout);
		if (ang != ang)
			return ;
		if (ang < ang_mem)
		{
			ang_mem = ang;
			id = cr->links[i]->id;
		}
		i++;
	}
	if (ang_mem == PI_CEIL)
		return;
	halfplane(cr, find_by_index(cr, id));
}

void				halfplane(t_core *cr, t_wall *ref)
{
	float		d;
	t_wall	*wall;
	int		i;
	t_wlink	*tmp;
	int		cycle = 0;

	i = 0;
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
					cr->clockwise = (wall->p2.x - ref->p1.x) * (ref->p2.y - ref->p1.y) - (wall->p2.y - ref->p1.y) * (wall->p2.x - ref->p1.x) > 0 ? 1 : 0;
					d = (wall->p2.x - ref->p1.x) * (ref->p2.y - ref->p1.y) - (wall->p2.y - ref->p1.y) * (wall->p2.x - ref->p1.x);
					if ((d < 0 && cr->clockwise > 0) || (d > 0 && cr->clockwise < 0))
					{
						wall->color = 0xff0000;
					}
					// printf("%f, I = %d\n", d, i);
				}
				else if ((wall->p2.x == ref->p1.x) && (wall->p2.y == ref->p1.y))
				{
					cr->clockwise = (wall->p2.x - ref->p1.x) * (ref->p2.y - ref->p1.y) - (wall->p2.y - ref->p1.y) * (wall->p2.x - ref->p1.x) > 0 ? 1 : 0;
					printf("ID: %d %d\n", wall->index, ref->index);
					if (wall->index == ref->index)
					{
						return ;
					}
					d = (wall->p1.x - ref->p1.x) * (ref->p2.y - ref->p2.y) - (wall->p1.y - ref->p1.y) * (wall->p1.x - ref->p1.x);
					printf("%f, I = %d\n", d, i);
					if ((d < 0 && cr->clockwise > 0) || (d > 0 && cr->clockwise < 0))
					{
						wall->color = 0xff0000;
						tmp = (t_wlink *)malloc(sizeof(t_wlink));
						tmp->p.x = wall->p1.x;
						tmp->p.y = wall->p1.y;
						tmp->id = wall->index;
						cr->links[i] = tmp;
						cr->links[i + 1] = NULL;
						i++;
					}
					// ref = wall;
					// wall = cr->wlist;
				}
			}
			wall = wall->next;
		}
		if (cr->links[0])
			calc_angle(cr, ref);
		return ;
	}
}
