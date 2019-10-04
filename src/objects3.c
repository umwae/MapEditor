/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/24 21:17:01 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <fcntl.h>

static void	restore_obj_id(t_core *cr)
{
	t_obj		*obj;
	int			i;

	i = 0;
	obj = *cr->olist;
	while (obj)
	{
		obj->id = i;
		i++;
		obj = obj->next;
	}
}

static void	del_object_part(t_core *cr, int idref, t_obj *pr, t_obj *obj)
{
	if (!pr->next)
		return ;
	obj = pr->next;
	if (!obj)
		return ;
	if (obj->id == idref)
	{
		pr->next = obj->next;
		free(obj);
		cr->closest_obj = NULL;
		restore_obj_id(cr);
		return ;
	}
}

void		del_object(t_core *cr, int idref)
{
	t_obj	*pr;
	t_obj	*obj;

	pr = *cr->olist;
	if (!pr)
		return ;
	if (pr->id == idref)
	{
		*cr->olist = pr->next;
		free(pr);
		cr->closest_obj = NULL;
		restore_obj_id(cr);
		return ;
	}
	while (pr)
	{
		del_object_part(cr, idref, pr, obj);
		pr = pr->next;
	}
}

float		sel_object(t_core *cr, int x, int y)
{
	t_obj	*obj;
	float	min_dist;
	float	res;

	min_dist = SELECT_RADIUS;
	obj = *cr->olist;
	restore_obj_color(cr);
	while (obj)
	{
		if ((res = calc_dist(x, y, obj->fcoord.x + cr->offs.x, \
		obj->fcoord.y + cr->offs.y)) < min_dist)
		{
			cr->closest_obj = obj;
			min_dist = res;
		}
		obj = obj->next;
	}
	return (min_dist);
}
