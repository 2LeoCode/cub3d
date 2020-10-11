/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 15:35:48 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/11 15:12:51 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 16
# endif
# define MAX_FD 9999

typedef struct		s_list
{
	char			buf[BUFFER_SIZE + 1];
	char			*pos;
	struct s_list	*next;
}					t_list;
typedef struct		s_buffer
{
	int				read_ret;
	int				init;
	int				id;
	t_list			*all;
	t_list			*last;
	t_list			*cur;
}					t_buffer;
int					get_next_line(int fd, char **line);
void				*lst_chr(t_list *lst, int c);
int					clear_buffer(t_buffer *buf);
#endif
