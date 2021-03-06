/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isascii.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 13:29:16 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/16 13:29:16 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_bool	ft_isspace(int c)
{
	return ((c && ft_strchr(" \n\t\r\f\v", c)) ? true : false);
}

t_bool	ft_isalpha(int c)
{
	return (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')));
}

t_bool	ft_isdigit(int c)
{
	return ((c >= '0') && (c <= '9'));
}
