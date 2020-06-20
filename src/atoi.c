/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 13:21:07 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/16 13:21:07 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int		ft_atoi(char *s)
{
	long	n;
	long	ng;

	ng = 1;
	n = 0;
	while (ft_isspace(*s))
		s++;
	if ((*s == '+') || (*s == '-'))
		ng = -1;
	while ((*s >= '0') && (*s <= '9'))
		n = ((n * 10) + (*(s++) - 48));
	n *= ng;
	if (n > INT_MAX)
		return (INT_MAX);
	if (n < INT_MIN)
		return (INT_MIN);
	return (n);
}
