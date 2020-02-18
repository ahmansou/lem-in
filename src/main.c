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
	else if (error == -2 || error == -4)
	{
		ft_putendl("Rooms Error");
		if (error == -4)
			ft_putendl("Start room or End room doesnt exist");
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
	if (!env->stend.start || !env->stend.end)
		return (-4);
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

	if ((env.error = get_data(&env)) <= 0 || !env.stend.start || !env.stend.end)
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