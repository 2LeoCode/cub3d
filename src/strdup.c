/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 22:58:38 by lsuardi           #+#    #+#             */
/*   Updated: 2020/10/10 22:05:34 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*ft_strdup(char *s)
{
	char	*tmp;
	size_t	len;

	len = ft_strlen(s);
	if (!(tmp = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (*s)
		*(tmp++) = *(s++);
	*tmp = 0;
	return (tmp - len);
}
