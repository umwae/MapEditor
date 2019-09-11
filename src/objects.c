/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/11 21:31:17 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

static int		count_obj(t_core *cr)
{
	t_obj	*obj;
	int		i;

	obj = cr->olist;
	while (obj)
	{
		obj = obj->next;
		i++;
	}
	return (i);
}

void		add_object(t_core *cr, int x, int y)
{
	t_obj	*obj;


	obj = (t_obj *)malloc(sizeof(t_obj));
	obj->next = cr->olist;
	obj->fcoord.x = x;
	obj->fcoord.y = y;
	obj->id = count_obj(cr) + 1;
	cr->olist = obj;
}

void		draw_objects(t_core *cr)
{
	t_obj		*obj;
	t_coord		xy;
	t_coord		ab;

	obj = cr->olist;
	ab.x = OBJECT_SIZE;
	ab.y = OBJECT_SIZE;
	while (obj)
	{
		xy.x = obj->fcoord.x - OBJECT_SIZE / 2 + cr->offs.x;
		xy.y = obj->fcoord.y - OBJECT_SIZE / 2 + cr->offs.y;
		draw_rectangle(cr, xy, ab, OBJECT_COLOR);
		obj = obj->next;
	}
}

void		del_object(t_core *cr, int idref)
{
	t_obj	*pr;
	t_obj	*obj;

	pr = cr->olist;
	if (pr->id == idref)
	{
		free(pr);
		cr->olist = NULL;
	}
	while (pr)
	{
		if (!pr->next)
		{
			return ;
		}
		obj = pr->next;
		if (obj->id == idref)
		{
			printf("obj del\n");
			pr->next = obj->next;
			free(obj);
			return ;
		}
		pr = pr->next;
	}
}
