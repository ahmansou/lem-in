/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 21:20:19 by ahmansou          #+#    #+#             */
/*   Updated: 2019/05/09 16:34:30 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	get_line(const int fd, char **tmpfd, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tmpfd[fd][i] != '\n' && tmpfd[fd][i])
		i++;
	if (tmpfd[fd][i] == '\n')
	{
		*line = ft_strsub(tmpfd[fd], 0, i);
		tmp = tmpfd[fd];
		tmpfd[fd] = ft_strdup(tmp + i + 1);
		free(tmp);
	}
	else if (tmpfd[fd][i] == '\0')
	{
		*line = ft_strdup(tmpfd[fd]);
		tmpfd[fd] = NULL;
	}
}

static int	get_next_line(const int fd, char **line)
{
	int			r;
	char		buff[BUFF_SIZE + 1];
	char		*tmp;
	static char *tmpfd[FD_LIMIT];

	while ((r = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if (!(buff[r] = '\0') && tmpfd[fd] != NULL)
		{
			tmp = ft_strdup(tmpfd[fd]);
			free(tmpfd[fd]);
		}
		else
			tmp = ft_strnew(0);
		tmpfd[fd] = ft_strjoin(tmp, buff);
		free(tmp);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (r == 0 && (tmpfd[fd] == NULL || tmpfd[fd][0] == '\0'))
		return (0);
	else if (r < 0 || fd < 0 || fd > FD_LIMIT)
		return (-1);
	get_line(fd, tmpfd, line);
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
