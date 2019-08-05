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

void			apply_sector(t_core *cr, t_wall *wall, int pr1, int pr2)
{
	(void)pr1;
	(void)pr1;
	if (wall->color != SEL_SEC_COLOR)
		return ;
	wall->color = APP_SEC_COLOR;
	if (wall->sectors[0] < 0)
		wall->sectors[0] = cr->sec_num;
	else if (wall->sectors[1] < 0)
		wall->sectors[1] = cr->sec_num;

}

void			turn_color(t_core *cr, t_wall *wall, int color1, int color2)
{
	if (wall->color == color1)
		wall->color = color2;
}

void			reset_color_exc(t_core *cr, t_wall *wall, int color1, int color2)
{
	if (wall->color != color1 && wall->color != color2)
	{
		if (wall->sectors[0] < 0 && wall->sectors[1] < 0)
			wall->color = WALL_COLOR;
		else
			wall->color = APP_SEC_COLOR;
	}
}

void			reset_color(t_core *cr)
{
	t_wall		*wall;

	wall = cr->wlist;
	if (!wall)
		return ;
	while (wall)
	{
		wall->color = WALL_COLOR;
		wall = wall->next;
	}
}
