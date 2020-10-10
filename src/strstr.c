/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 21:58:44 by lsuardi           #+#    #+#             */
/*   Updated: 2020/10/10 15:31:51 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*ft_strstr(char *haystack, char *needle)
{
	size_t	n;

	n = ft_strlen(needle);
	while (haystack && needle && *haystack)
	{
		while (*haystack && (*haystack - *needle))
			haystack++;
		if (!ft_memcmp(haystack, needle, n))
			return (haystack);
		haystack += (*haystack != 0);
	}
	return (NULL);
}
