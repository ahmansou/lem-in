/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 12:49:50 by ahmansou          #+#    #+#             */
/*   Updated: 2020/01/25 12:49:52 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	error_man(int error, int ant)
{
	if (error == -1)
		ft_printf("Double ##Start or ##end\n");
	else if (error == 0)
		ft_printf("Random Error\n");
	else if (error == -2)
		ft_printf("Room Error\n");
	else if (error == -4)
		ft_printf("Room in link Not found\n");
	else if (error == -5)
		ft_printf("Link has the same room\n");
	else if (error == -6)
		ft_printf("Link syntax error\n");
	else if (ant == -7)
		ft_printf("No ants or number of ants is negative\n");
	else if (ant == -8)
		ft_printf("\n");
	else if (error == -9)
		ft_printf("Empty line\n");
}

int			get_ants(char *s)
{
	long long int	ant;

	ant = ft_atoi(s);
	if (!is_num(s) || ant < 0)
		return (-7);
	return (ant);
}

int			main(void)
{
	t_lines	*lines;
	t_rooms *rooms;
	t_ht	**ht;
	t_stend stend;
	int		score;
	t_path	***path;
	int error;

	error = 0;
	if (!get_lines(&lines))
	{
		ft_printf("error lines\n");
		return (0);
	}
	// ft_printf("%d\n", get_lines(&lines));
	rooms = NULL;
	stend.start = NULL;
	stend.end = NULL;
	if ((stend.ants = get_ants(lines->line)) <= 0)
	{
		free_lines(&lines);
		error_man(error, stend.ants);
		return (0);
	}
	if ((error = get_assets(&rooms, lines->next, &stend)) <= 0)
	{
		free_lines(&lines);
		free_rooms(&rooms);
		free_stend(&stend);
		error_man(error, stend.ants);
		return (0);
	}
	if (!(ht = create_ht(rooms)))
	{
		ft_printf("Hash table error\n");
		free_lines(&lines);
		free_rooms(&rooms);
		free_stend(&stend);
		free_ht(&ht);
		return (0);
	}
	if (!(path = solver(rooms, &ht, stend)))
	{
		ft_printf("ERROR");
		free_lines(&lines);
		free_rooms(&rooms);
		free_stend(&stend);
		free_ht(&ht);
		return (0);
	}
	score = git_scores(path, st_links(ht, stend.start), stend);
	if (!antman(path[score], score, stend, lines))
	{
		ft_printf("anties error");
		free_lines(&lines);
		free_rooms(&rooms);
		free_stend(&stend);
		free_ht(&ht);
		free_paths(&path, st_links(ht, stend.start));
	}
	free_paths(&path, st_links(ht, stend.start));
	free_lines(&lines);
	free_rooms(&rooms);
	free_stend(&stend);
	free_ht(&ht);
	ft_putendl("");
	return (0);
}
