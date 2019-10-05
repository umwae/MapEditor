/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/24 20:53:21 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <fcntl.h>

void		err_ex(int pr)
{
	if (pr == 0)
		ft_putstr("Error: memory allocation failure\n");
	else if (pr == 1)
		ft_putstr("Error: unexpected GNL data\n");
	exit(1);
}

void		reopen_10_times(int *fd)
{
	int		i;

	i = 10;
	while (i-- && (*fd = open(SAVEPATH, O_RDONLY)) < 0)
	{
	}
	if (*fd < 0)
		err_ex(1);
}

int			check_bounds(int x, int y)
{
	if (x >= WIN_WIDTH || y >= WIN_HIGHT || \
		x < 0 || y < 0)
		return (1);
	return (0);
}

int			min(int a, int b)
{
	return (a < b ? a : b);
}

int			max(int a, int b)
{
	return (a > b ? a : b);
}
