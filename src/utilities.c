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

void	err_ex(int pr)
{
	if (pr == 0)
		ft_putstr("Error: memory allocation failure\n");
	exit(1);
}

int				 		min(int a, int b)
{
	return (a < b ? a : b);
}

int 					max(int a, int b)
{
	return (a > b ? a : b);
}

float					calc_dist(int x0, int y0, int x1, int y1)
{
	int	dx;
	int	dy;

	dx = abs(x0) > abs(x1) ? x0 - x1 : x1 - x0;
	dy = abs(y0) > abs(y1) ? y0 - y1 : y1 - y0;
	return (sqrt(pow(dx, 2) + pow(dy, 2)));
}
