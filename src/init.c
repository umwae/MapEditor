/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:55:20 by jsteuber          #+#    #+#             */
/*   Updated: 2019/08/31 17:55:51 by jsteuber         ###   ########.fr       */
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
	cr->zoom = 1;
	cr->ctrl_button = 0;
	img_new(cr);
	redraw(cr);
}
