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
	int		i;

	i = 0;
	while (haystack && needle && *haystack && needle[i])
	{
		i = 0;
		while (*haystack && (*haystack - *needle))
			haystack++;
		while (haystack[i] && needle[i] && (haystack[i] == needle[i]))
			i++;
		haystack += (needle[i] != 0);
	}
	return ((!needle || needle[i]) ? NULL : haystack);
}
