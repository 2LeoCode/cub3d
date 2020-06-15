/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 22:42:11 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/14 22:42:11 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int		ft_fputc(int fd, char c)
{
	unsigned char	tmp;

	tmp = (unsigned char)c;
	if (fd > 0 && (write(fd, &tmp, 1) < 1))
		return (-1);
	return (c);
}

int		ft_fputs(int fd, char *s)
{
	int		i;

	i = -1;
	if (!s)
		return (ft_fputs(fd, "(null)"));
	while (s[++i])
		if (ft_fputc(fd, s[i]) == -1)
			return (-1);
	return (i + (i < 0));
}

int		ft_putchar(char c)
{
	unsigned char	tmp;

	tmp = (unsigned char)c;
	write(1, &tmp, 1);
	return (c);
}

int		ft_putstr(char *s)
{
	int		i;

	i = -1;
	if (!s)
		return (ft_putstr("(null)"));
	while (s[++i])
		ft_putchar(s[i]);
	return (i + (i < 0));
}
