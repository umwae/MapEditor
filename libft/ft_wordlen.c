/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 18:51:58 by jsteuber          #+#    #+#             */
/*   Updated: 2019/02/19 18:00:45 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int		ft_wordlen(char *start, char c)
{
	unsigned int		i;

	i = 0;
	while (start[i] != c && start[i] != '\0')
	{
		i++;
	}
	return (i);
}
