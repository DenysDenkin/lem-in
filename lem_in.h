/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 18:12:15 by ddenkin           #+#    #+#             */
/*   Updated: 2018/03/16 18:11:07 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# define INF 2147483647

typedef struct		s_room
{
	int				distance;
	char			*name;
	int				x;
	int				y;
	int				next;
}					t_room;

typedef struct		s_info
{
	char			**tab;
	int				cursize;
	int				maxsize;
}					t_info;

typedef struct		s_path
{
	int				**path;
	int				cursize;
	int				maxsize;
}					t_path;

typedef struct		s_farm
{
	int				ants;
	t_room			**rooms;
	int				nrooms;
	int				start;
	int				end;
	int				**links;
	int				*occupied;
	t_path			*paths;
	int				*distribution;
	t_info			*info;
}					t_farm;

typedef struct		s_iter
{
	int				i;
	int				j;
	int				k;
}					t_iter;

void				add_info(t_info *info, char *line);
void				add_path(t_path *paths, int *path);
t_info				*init_info(void);
t_path				*init_paths(void);
t_farm				*init_farm();
int					**init_links(t_farm *farm);
t_room				**init_rooms(t_farm *farm);
int					*init_occupied(t_farm *farm);
int					*init_ants(t_farm *farm, int start);
int					parse_input(t_farm *farm);
int					is_valid_line(t_farm *farm, char *line);
int					room_n(const char *room, t_farm *farm);

void				error(char *str);
int					nerror(char *str);
void				print_ants(t_farm *farm, int *ants);
void				print_ant(t_farm *farm, int ant, int *ants, int first);
void				print_occupation(t_farm *farm);
void				drop_out(t_farm *farm);

void				minimize_distances(t_farm *farm, int room);
void				recount_distances(t_farm *farm, int *dist, int room);
void				optimize_positions(t_farm *farm, int *ants, int first);
void				lemmings(t_farm *farm);
int					*copy_distances(t_farm *farm);
int					room_n(const char *room, t_farm *farm);
int					parse_ants(t_farm *farm, char *line, int *stage);
int					coords_ok(t_farm *farm, int roomn);
#endif
