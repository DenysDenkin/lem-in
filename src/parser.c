/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 17:15:20 by ddenkin           #+#    #+#             */
/*   Updated: 2018/03/16 15:43:19 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int			parse_link(t_farm *farm, char *line)
{
	char	**tab;

	tab = ft_strsplit(line, '-');
	if (count_words(line, '-') != 2 || ft_count_symb(line, '-') != 1
		|| room_n(tab[0], farm) == -1 || room_n(tab[1], farm) == -1)
	{
		freetab((void ***)&tab, -1);
		free(line);
		return (0);
	}
	farm->links[room_n(tab[0], farm)][room_n(tab[1], farm)] = 1;
	farm->links[room_n(tab[1], farm)][room_n(tab[0], farm)] = 1;
	freetab((void ***)&tab, -1);
	add_info(farm->info, line);
	return (1);
}

int			parse_room(t_farm *farm, char *line, int *s_e)
{
	char	**tab;

	tab = ft_strsplit(line, ' ');
	if (ft_count_symb(line, ' ') != 2 || count_words(line, ' ') != 3 ||
			ft_strchr(line, '-') || tab[0][0] == 'L' || room_n(tab[0], farm)
			!= -1 || !ft_isnumber(tab[1]) || !ft_isnumber(tab[2]))
		return (nerror("room error"));
	farm->rooms[farm->nrooms]->name = ft_strdup(tab[0]);
	farm->rooms[farm->nrooms]->x = ft_atoi(tab[1]);
	farm->rooms[farm->nrooms]->y = ft_atoi(tab[2]);
	if ((*s_e == 1 && farm->start != -1) || (*s_e == 2 && farm->end != -1)\
										|| coords_ok(farm, farm->nrooms))
		return (nerror("duplicate start or end or invalid coords"));
	(*s_e == 1) ? farm->start = farm->nrooms : 1;
	(*s_e == 2) ? farm->end = farm->nrooms : 1;
	*s_e = 0;
	farm->nrooms++;
	freetab((void ***)(&tab), -1);
	add_info(farm->info, line);
	return (0);
}

int			stage_1(t_farm *farm, char *line, int *s_e, int *stage)
{
	if (line[0] == '#')
	{
		(ft_strequ(line, "##start") == 1) ? *s_e = 1 : 1;
		(ft_strequ(line, "##end") == 1) ? *s_e = 2 : 1;
		add_info(farm->info, line);
	}
	else if (count_words(line, ' ') != 3 && count_words(line, '-') == 2)
	{
		(*stage)++;
		(!farm->links) ? farm->links = init_links(farm) : 0;
	}
	else if (parse_room(farm, line, s_e) == -1)
		return (-1);
	return (0);
}

int			add_el(t_farm *farm, char *line)
{
	static int	stage = 0;
	static int	s_e = 0;

	if (line[0] == '#' && !(stage == 1 && (ft_strequ("##start", line)\
										|| ft_strequ("##end", line))))
	{
		add_info(farm->info, line);
		return (1);
	}
	if (stage == 0)
	{
		if (parse_ants(farm, line, &stage) == -1)
			return (-1);
	}
	else if (stage == 1)
		if (stage_1(farm, line, &s_e, &stage) == -1)
			return (-1);
	if (stage == 2)
		return (parse_link(farm, line));
	return (1);
}

int			parse_input(t_farm *farm)
{
	char	*line;
	int		status;

	farm->info = init_info();
	farm->rooms = init_rooms(farm);
	status = -1;
	while (get_next_line(0, &line) > 0 && line[0])
		if ((status = add_el(farm, line)) == 0)
			break ;
		else if (status == -1)
			return (-1);
	if (status == -1)
		return (nerror("Empty farm"));
	return (1);
}
