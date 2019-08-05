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

static int				calc_angle(t_core *cr, t_wall *ref, t_coord *wp, int id, t_coord *refpoint, t_coord *refstart)
{
	float	c;
	float	b;
	float	a;
	float	angle;

	c = ref->len;
	a = calc_dist(refstart->x, refstart->y, wp->x, wp->y);
	b = calc_dist(refpoint->x, refpoint->y, wp->x, wp->y);
	angle = acos((b * b + c * c - a * a) / (2 * b * c));
	printf("angle %f\n", angle);
	if (angle < cr->angle_mem)
	{
		cr->angle_mem = angle;
		cr->idcurr = id;
		cr->wpoint = cr->wpoint_tmp;
	}
	if (cr->angle_mem == PI_CEIL)
		return (0);
	return (1);
}

static int	compare_walls(t_core *cr, t_wall *ref, t_wall *wall, t_coord *refpoint, t_coord *refstart)
{
	t_coord	wallpoint;
	float		d;

	printf("comparing ID%d and ID%d\n", ref->index, wall->index);
	if (wall->index == ref->index)
		return (0);
	if ((wall->p1.x == refpoint->x) && (wall->p1.y == refpoint->y))
	{
		wallpoint.x = wall->p2.x;
		wallpoint.y = wall->p2.y;
		cr->wpoint_tmp = 2;
		printf("connected with P1\n");
	}
	else if ((wall->p2.x == refpoint->x) && (wall->p2.y == refpoint->y))
	{
		wallpoint.x = wall->p1.x;
		wallpoint.y = wall->p1.y;
		printf("connected with P2\n");
		cr->wpoint_tmp = 1;
	}
	else
		return (0);
	d = (refpoint->x - refstart->x) * (wallpoint.y - refstart->y) - \
	(refpoint->y - refstart->y) * (wallpoint.x - refstart->x);
	// (bx-ax)*(py-ay)-(by-ay)*(px-ax)
	printf("side %f\n", d);
	if ((d < 0 && cr->wside == 0) || (d > 0 && cr->wside == 1))
	{
		calc_angle(cr, ref, &wallpoint, wall->index, refpoint, refstart);
	}
	return (0);
}

void				halfplane(t_core *cr, t_wall *ref)
{
	t_wall	*wall;
	t_coord	refpoint;
	t_coord	refstart;

	cr->angle_mem = PI_CEIL;
	cr->idcurr = 0;
	if (ref->color == SEL_SEC_COLOR)
		return ;
	cr->sec_num++;
	printf("=============\nclickside: %d || ", cr->wside);
	if (cr->wpoint == 2)
	{
		refpoint.x = ref->p2.x;
		refpoint.y = ref->p2.y;
		refstart.x = ref->p1.x;
		refstart.y = ref->p1.y;
		printf("refpoint: 2\n");
	}
	else
	{
		refpoint.x = ref->p1.x;
		refpoint.y = ref->p1.y;
		refstart.x = ref->p2.x;
		refstart.y = ref->p2.y;
		printf("refpoint: 1\n");
	}
	cr->wside = (refpoint.x - refstart.x) * (cr->click.y - refstart.y) - \
	(refpoint.y - refstart.y) * (cr->click.x - refstart.x) > 0 ? 1 : 0;
	//	(bx-ax)*(py-ay)-(by-ay)*(px-ax)
	wall = cr->wlist;
	if (!wall || !ref)
		return ;
	while (wall)
	{
		compare_walls(cr, ref, wall, &refpoint, &refstart);
		wall = wall->next;
	}
	ref->color = SEL_SEC_COLOR;
	halfplane(cr, find_by_index(cr, cr->idcurr));
}
