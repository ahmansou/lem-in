/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <ahmansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 21:20:19 by ahmansou          #+#    #+#             */
/*   Updated: 2020/02/27 15:09:31 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static char	*ft_join(char *str, char *buf)
{
	char	*res;

	res = ft_strjoin(str, buf);
	free(str);
	return (res);
}

static int	get_next_line(const int fd, char **line)
{
	char		*str;
	char		buf[2];
	size_t		size;

	if (read(fd, buf, 0) < 0)
		return (-1);
	ft_bzero(buf, 2);
	str = ft_strnew(0);
	while ((size = read(fd, buf, 1)) > 0)
	{
		if (*buf == '\n')
			break ;
		str = ft_join(str, buf);
	}
	if (!*buf)
	{
		free(str);
		return (0);
	}
	*line = str;
	return (1);
}

static int	add_line(t_lines **lines, char *line)
{
	t_lines *new;
	t_lines *tmp;

	if (!(new = (t_lines*)malloc(sizeof(t_lines))))
		return (0);
	if (!(new->line = ft_strdup(line)))
		return (0);
	new->next = NULL;
	tmp = *lines;
	if (*lines == NULL)
	{
		*lines = new;
		return (1);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

int			get_lines(t_lines **lines)
{
	int		ret;
	char	*line;

	*lines = NULL;
	while ((ret = get_next_line(0, &line)))
	{
		if (!ft_strcmp(line, ""))
		{
			ft_strdel(&line);
			return (0);
		}
		if (!add_line(lines, line))
		{
			ft_strdel(&line);
			return (0);
		}
		ft_strdel(&line);
	}
	if (ret < 0)
		return (0);
	return (1);
}

void		print_lines(t_lines *lines)
{
	t_lines	*tline;

	tline = lines;
	while (tline)
	{
		ft_putendl(tline->line);
		tline = tline->next;
	}
	ft_putendl("");
}
