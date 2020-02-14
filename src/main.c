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

static void	err_man(int error, t_lemin_env *env)
{
	if (error == 0)
	{
		ft_putendl("Read Error");
		free_lines(&(env->lines));
	}
	else if (error == -1)
		ft_putendl("Ants Error");
	else if (error == -2)
	{
		ft_putendl("Rooms Error");
		free_lines(&(env->lines));
		free_rooms(&(env->rooms));
		free_stend(&(env->stend));
	}
	else if (error == -3)
	{
		ft_putendl("Hash Table Error");
		free_lines(&(env->lines));
		free_rooms(&(env->rooms));
		free_stend(&(env->stend));
		free_ht(&(env->ht));
	}
}

static void	err_man_proc(int error, t_lemin_env *env)
{
	if (error == 0)
	{
		ft_putendl("Solver Error");
		free_lines(&(env->lines));
		free_rooms(&(env->rooms));
		free_stend(&(env->stend));
		free_ht(&(env->ht));
	}
	else if (error == -1)
	{
		ft_putendl("Ant Manager Error");
		free_paths(&env->path, st_links(env->ht, env->stend.start));
		free_lines(&(env->lines));
		free_rooms(&(env->rooms));
		free_stend(&(env->stend));
		free_ht(&(env->ht));
	}
}

int			get_data(t_lemin_env *env)
{
	env->rooms = NULL;
	env->ht = NULL;
	env->stend.start = NULL;
	env->stend.end = NULL;
	if (!get_lines(&env->lines))
		return (0);
	if ((env->stend.ants = get_ants(env->lines->line)) <= 0)
		return (-1);
	if (get_assets(&env->rooms, env->lines->next, &env->stend) <= 0)
		return (-2);
	if (!(env->ht = create_ht(env->rooms)))
		return (-3);
	return (1);
}

int			process_data(t_lemin_env *env)
{
	env->path = NULL;
	if (!(env->path = solver(env->rooms, &env->ht, env->stend)))
		return (0);
	env->score = git_scores(env->path,
		st_links(env->ht, env->stend.start), env->stend);
	if (!antman(env->path[env->score], env->score, env->stend, env->lines))
		return (-1);
	return (1);
}

int			main(void)
{
	t_lemin_env	env;

	if ((env.error = get_data(&env)) <= 0)
	{
		err_man(env.error, &env);
		return (0);
	}
	if ((env.error = process_data(&env)) <= 0)
	{
		err_man_proc(env.error, &env);
		return (0);
	}
	free_paths(&(env.path), st_links(env.ht, env.stend.start));
	free_lines(&(env.lines));
	free_rooms(&(env.rooms));
	free_stend(&(env.stend));
	free_ht(&(env.ht));
	return (0);
}

/*
**	static void	error_man(int error, int ant)
**	{
**		if (error == -1)
**			ft_printf("Double ##Start or ##end\n");
**		else if (error == 0)
**			ft_printf("Random Error\n");
**		else if (error == -2)
**			ft_printf("Room Error\n");
**		else if (error == -4)
**			ft_printf("Room in link Not found\n");
**		else if (error == -5)
**			ft_printf("Link has the same room\n");
**		else if (error == -6)
**			ft_printf("Link syntax error\n");
**		else if (ant == -7)
**			ft_printf("No ants or number of ants is negative\n");
**		else if (ant == -8)
**			ft_printf("\n");
**		else if (error == -9)
**			ft_printf("Empty line\n");
**	}
*/

/*
**	int			main(void)
**	{
**		t_lines	*lines;
**		t_rooms *rooms;
**		t_ht	**ht;
**		t_stend stend;
**		t_path	***path;
**		int		score;
**		int		error;
**
**		error = 0;
**		if (!get_lines(&lines))
**		{
**			ft_printf("error lines\n");
**			return (0);
**		}
**		rooms = NULL;
**		stend.start = NULL;
**		stend.end = NULL;
**		if ((stend.ants = get_ants(lines->line)) <= 0)
**		{
**			free_lines(&lines);
**			error_man(error, stend.ants);
**			return (0);
**		}
**		if ((error = get_assets(&rooms, lines->next, &stend)) <= 0)
**		{
**			free_lines(&lines);
**			free_rooms(&rooms);
**			free_stend(&stend);
**			error_man(error, stend.ants);
**			return (0);
**		}
**		if (!(ht = create_ht(rooms)))
**		{
**			ft_printf("Hash table error\n");
**			free_lines(&lines);
**			free_rooms(&rooms);
**			free_stend(&stend);
**			free_ht(&ht);
**			return (0);
**		}
**		if (!(path = solver(rooms, &ht, stend)))
**		{
**			ft_printf("ERROR");
**			free_lines(&lines);
**			free_rooms(&rooms);
**			free_stend(&stend);
**			free_ht(&ht);
**			return (0);
**		}
**		score = git_scores(path, st_links(ht, stend.start), stend);
**		if (!antman(path[score], score, stend, lines))
**		{
**			ft_printf("anties error");
**			free_lines(&lines);
**			free_rooms(&rooms);
**			free_stend(&stend);
**			free_ht(&ht);
**			free_paths(&path, st_links(ht, stend.start));
**		}
**		free_paths(&path, st_links(ht, stend.start));
**		free_lines(&lines);
**		free_rooms(&rooms);
**		free_stend(&stend);
**		free_ht(&ht);
**		ft_putendl("");
**		return (0);
**	}
*/
