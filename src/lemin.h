/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 12:46:01 by ahmansou          #+#    #+#             */
/*   Updated: 2020/01/25 12:46:02 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# define BUFF_SIZE 1
# define FD_LIMIT 4864
# define TABLE_SIZE 1000

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include "../libft/libft.h"
# include "../ft_printf/src/ft_printf.h"

typedef struct 		s_lines
{
	char			*line;
	struct s_lines	*next;
}					t_lines;

typedef	struct		s_link
{
	// char			*link;
	struct s_rooms	*link;
	int				flow;
	struct s_link	*next;
}					t_link;

typedef struct		s_rooms
{
	char			*room;
	int				visited;
	int				cap;
	int				flag;
	t_link			*links;
	struct s_rooms	*prev;
	struct s_rooms	*next;
}					t_rooms;

typedef struct		s_stend
{
	int se;
	int				ants;
	char			*start;
	char			*end;
}					t_stend;

typedef struct		s_ht
{
	t_rooms			*room;
	struct s_ht		*next;
}					t_ht;

typedef struct		s_q
{
	t_rooms			*element;
	struct s_q		*next;
	// struct s_q		*prev;
}					t_q;

typedef struct		s_path
{
	struct s_rooms	*room;
	int				length;
	int				busy;
	struct s_path	*next;
}					t_path;

typedef struct		s_score_env
{
	int				i;
	int				j;
	int				best_score[2];
	int				i_score;
	int				nrooms;
	struct s_path	*tpath;

}					t_score_env;

// get_next_line.c
int					get_lines(t_lines **lines);
void				free_lines(t_lines **lines);

// line_misc.c
int					is_comment(char *s);
int					is_room(char *s);
int					is_stend(char *s);

// get_assets.c
int					get_assets(t_rooms **rooms, t_lines *l, t_stend *stend);

// get_room.c
int					get_room(t_rooms **rooms, char *line, t_stend *stend);

//get_links.c

int					get_links(t_rooms **rooms, t_lines *lines);

// hash_table.c
t_ht				**create_ht(t_rooms *room);

// misc_room.c
void				free_rooms(t_rooms **rooms);
int					st_end(char *room, t_stend *stend, int se);

// misc.c 
int					is_num(char *s);
unsigned int		hash(const char *name);
int					num_links(t_rooms *room);
int					path_size(t_path *path);

// bfs.c
t_path				***solver(t_rooms *rooms, t_ht ***ht, t_stend se);

// get_paths.c
int     			get_path(t_ht ***ht, t_rooms **rooms,
							t_path **path, t_stend se);
void				sort_paths(t_path ***path, int npath);

// path_misc.c
int					st_links(t_ht **ht, char *st);
int					git_scores(t_path ***path, int stlink, t_stend se);

// correction.c 
void				correction(t_ht ***ht, t_stend se);
void				reset_graph(t_rooms **room);

// antman.c

void				antman(t_path **path, int npath, t_stend se, t_ht **ht);

#endif
