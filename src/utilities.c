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


// char		*ft_ftoa(float num)
// {
// 	short	i;
// 	int		tmp;
// 	short	size;
// 	char	*str;
//
// 	i = 0;
// 	size = 1;
// 	tmp = (int)round(num * 100);
// 	if (num == .0)
// 		return (ft_strdup("0.00"));
// 	(num < .0 && (tmp *= -1.) > 0) ? ++size : 1;
// 	(tmp < 100) ? ++size : 1;
// 	num = tmp;
// 	while (tmp != 0 && ++size)
// 		tmp /= 10;
// 	if (!(str = (char *)malloc((size + 1) * sizeof(char))))
// 		return (NULL);
// 	str[size--] = 0;
// 	while ((int)num != 0 && ++i)
// 		(i != 3 && (str[size--] =
// 		((int)num % 10) + '0')) ? (num /= 10) : (str[size--] = '.');
// 	(i++ == 2) ? str[size--] = '.' : 1;
// 	(i++ == 3) ? str[size--] = '0' : 1;
// 	(size == 0) ? str[0] = '-' : 1;
// 	return (str);
// }

// static void	float_repair(float num)
// {
// 	num = floor()
// }

char		*ft_ftoa(float num)
{
	char	*str;

	char	*tmpm;
	char	*tmpa;
	int		i;
	int		size;
	int		restr;
	float		mem;


	restr = 2;
	mem = num;
	i = num >= 0 ? floor(num) : ceil(num);
	num = num - i;
	num = fabs(num * 100);
	num = round(num);
	if (num == 100)
	{
		num = 0;
		i += mem > 0 ? 1 : -1;
	}
	tmpm = ft_itoa(abs(i));
	// while (num - num / 10 != 0 && restr--)
	// 	num *= 10;
	tmpa = ft_itoa(num);
	if (!(str = ft_strnew(ft_strlen(tmpm) + ft_strlen(tmpa))))
		return (NULL);
	ft_strcat(str, mem >= 0 ? "" : "-");
	ft_strcat(str, tmpm);
	ft_strcat(str, ".");
	if (floor(num) != 0)
		ft_strcat(str, tmpa);
	else
		ft_strcat(str, "00");
	return (str);
}


double	ft_atof(const char *str)
{
	double	res;
	double	res2;
	char	*c;
	int		len;
	int		sign;
	char	*r2;

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
	*(c + 1) = ' ';
	res2 = (double)ft_atoi(c);
	//len = ft_strlen(c);
	len = 1;
	while (len--)
		res2 /= 10;
	return ((res + res2) * sign);
}

void			checkbox_fill(t_core *cr, t_coord xy, t_coord ab)
{
	xy.x = xy.x + ab.x * 0.1;
	xy.y = xy.y + ab.y * 0.1;
	ab.x *= 0.8;
	ab.y *= 0.8;
	draw_rectangle(cr, xy, ab, 0);
}

int				ft_arrlen(char	**arr)
{
	int		i;

	i = 0;
	if (!arr)
		return(0);
	while(arr[i])
		i++;
	return(i);
}