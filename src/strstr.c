/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 21:58:44 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/14 21:58:44 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*ft_strstr(char *haystack, char *needle)
{

	while (haystack && needle && *haystack && needle[i])
	{
		while (*haystack && (*haystack - *needle))
			haystack++;
		if (!ft_memcmp(haystack, needle, ft_strlen(needle)))
			return (haystack);
		haystack++;
	}
	return (NULL);
}
