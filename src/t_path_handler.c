/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_path_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 18:30:09 by ddenkin           #+#    #+#             */
/*   Updated: 2018/03/08 18:30:13 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_path		*init_paths(void)
{
	t_path	*res;

	res = (t_path *)malloc(sizeof(t_path));
	res->cursize = 0;
	res->maxsize = 16;
	res->path = (int **)malloc(sizeof(int *) * (res->maxsize + 1));
	res->path[res->maxsize] = 0;
	return (res);
}

void		add_path(t_path *paths, int *path)
{
	int		i;
	int		**newpath;

	if (paths->cursize >= paths->maxsize)
	{
		newpath = (int **)malloc(sizeof(int *) * (paths->maxsize * 2 + 1));
		i = -1;
		while (++i < paths->maxsize)
			newpath[i] = paths->path[i];
		free(paths->path);
		paths->path = newpath;
		paths->maxsize *= 2;
		paths->path[paths->maxsize] = 0;
	}
	paths->path[paths->cursize] = path;
	paths->cursize++;
}

int			parse_ants(t_farm *farm, char *line, int *stage)
{
	int p;

	if (ft_isnumber(line) && line[0] != '0' && (p = ft_atoi(line)) > 0)
		farm->ants = p;
	else
		return (nerror("No ants"));
	add_info(farm->info, line);
	(*stage)++;
	return (0);
}

int			coords_ok(t_farm *farm, int roomn)
{
	int		i;
	int		x;
	int		y;

	i = -1;
	x = farm->rooms[roomn]->x;
	y = farm->rooms[roomn]->y;
	while (++i < roomn)
		if (x == farm->rooms[i]->x && y == farm->rooms[i]->y)
			return (1);
	return (0);
}
