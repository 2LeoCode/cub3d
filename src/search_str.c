/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 21:54:23 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/14 21:54:23 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

char	*search_str(char *needle, char **ar, int size, int how)
{
	char	*tmp;

	while (size--)
		if ((tmp = ft_strstr(ar[size], needle)) != NULL)
		{
			if ((how == ANY)
			|| ((how == ALL) && (tmp == ar[size]) && !ft_strcmp(tmp, needle))
			|| ((how == BEG) && (tmp == ar[size]))
			|| ((how == END) && !ft_strcmp(tmp, needle)))
				return (ar[size]);
		}
	return (NULL);
}
