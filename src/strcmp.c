/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 22:27:29 by lsuardi           #+#    #+#             */
/*   Updated: 2020/10/10 23:15:13 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int		ft_memcmp(void *m1, void *m2, size_t n)
{
	int		i;

	i = -1;
	while (++i < n)
		if (*((unsigned char*)(m1 + i)) - ((unsigned char*)(m2 + i)))
			return (*((unsigned char*)(m1 + i)) - ((unsigned char*)(m2 + i)));
	return (0);
}

int		ft_strcmp(char *s1, char *s2)
{
	while (s1 && s2 && *s1 && *s2 && (*(s1++) == *(s2++)))
		continue ;
	return ((unsigned char)*(s1 - 1) - (unsigned char)*(s2 - 1));
}
