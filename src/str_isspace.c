/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_isspace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 21:20:25 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/17 21:20:25 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_bool	str_isspace(char *s)
{
	printf("lol\n");
	while (ft_isspace(*s))
		s++;
	printf("mdr\n");
	return (*s ? false : true);
}
