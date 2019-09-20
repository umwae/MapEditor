/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:55:20 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/20 19:51:51 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "editor.h"
#include <time.h>
#include <stdio.h>

void				init(t_core		*cr)
{
	if (!(cr->mlx = mlx_init()))
		err_ex(0);
	if (!(cr->win = mlx_new_window(cr->mlx, WIN_WIDTH, WIN_HIGHT, "Editor")))
		err_ex(0);
	cr->wlist = NULL;
	// cr->olist = NULL;
	cr->olist = (t_obj **)malloc(sizeof(t_obj *));
	*cr->olist = NULL;
	cr->slist = (t_sec **)malloc(sizeof(t_sec *));
	*cr->slist = NULL;
	load_gui(cr);
	cr->inst_func = draw_wall;
	cr->messages = (t_list **)malloc(sizeof(t_list **));
	*(cr->messages) = NULL;
	cr->highlight = 1;
	cr->sec_num = 0;
	cr->mpsw = 0;
	cr->offs.x = WIN_WIDTH / 2;
	cr->offs.y = WIN_HIGHT / 2;
	cr->test = -1;
	cr->zoom = 20;
	cr->ctrl_button = 0;
	cr->player.fcoord.x = 0;
	cr->player.fcoord.y = 0;
	cr->player.sec = 0;
	cr->player.angle = 0;
	cr->searchtype = 1;
	img_new(cr);
	redraw(cr);
}
