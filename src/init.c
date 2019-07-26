/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:55:20 by jsteuber          #+#    #+#             */
/*   Updated: 2019/07/26 18:33:59 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "editor.h"
#include <time.h>
#include <stdio.h>

void		init(t_core		*cr)
{
	if (!(cr->mlx = mlx_init()))
		err_ex(0);
	if (!(cr->win = mlx_new_window(cr->mlx, WIN_WIDTH, WIN_HIGHT, "Editor")))
		err_ex(0);
	// if (!(cr->sectors = (t_wall *)malloc(sizeof(t_wall))))
	// 	err_ex(0);
	// cr->sectors->next = NULL;
	// cr->sectors->walls = NULL;
	cr->vs.color = 0xffffff;
	img_new(cr);
}
