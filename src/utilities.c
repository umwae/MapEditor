/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/05 20:02:57 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int		check_bounds(int x, int y)
{
	if (x >= WIN_WIDTH || y >= WIN_HIGHT || \
		x < 0 || y < 0)
		return (1);
	return (0);
}

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


char		*ft_ftoa(float num)
{
	short	i;
	int		tmp;
	short	size;
	char	*str;

	i = 0;
	size = 1;
	tmp = (int)round(num * 100);
	if (num == .0)
		return (ft_strdup("0.00"));
	(num < .0 && (tmp *= -1.) > 0) ? ++size : 1;
	(tmp < 100) ? ++size : 1;
	num = tmp;
	while (tmp != 0 && ++size)
		tmp /= 10;
	if (!(str = (char *)malloc((size + 1) * sizeof(char))))
		return (NULL);
	str[size--] = 0;
	while ((int)num != 0 && ++i)
		(i != 3 && (str[size--] =
		((int)num % 10) + '0')) ? (num /= 10) : (str[size--] = '.');
	(i++ == 2) ? str[size--] = '.' : 1;
	(i++ == 3) ? str[size--] = '0' : 1;
	(size == 0) ? str[0] = '-' : 1;
	return (str);
}



double	ft_atof(const char *str)
{
	double	res;
	double	res2;
	char	*c;
	int		len;
	int		sign;

	sign = 1;
	c = (char *)str;
	while (!ft_isdigit(*c) && *c)
	{
		if (*c == '-')
			sign = -1;
		c++;
	}
	res = (double)ft_atoi(c);
	while (*c && *c != '.')
		c++;
	if (*c == '.')
		c++;
	res2 = (double)ft_atoi(c);
	//len = ft_strlen(c);
	len = 2;
	while (len--)
		res2 /= 10;
	return ((res + res2) * sign);
}
