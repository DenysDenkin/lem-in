/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddenkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 17:14:59 by ddenkin           #+#    #+#             */
/*   Updated: 2018/03/16 21:33:42 by ddenkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void		error(char *str)
{
	ft_putstr("Error: ");
	ft_putstr(str);
	ft_putstr(".\n");
}

int			nerror(char *str)
{
	error(str);
	return (-1);
}

void		print_ant(t_farm *farm, int ant, int *ants, int first)
{
	double	c;
	double	coef;

	coef = (double)((ant + 2) / 3 * 3) / farm->ants;
	if (ant % 3 == 0)
		c = SBLUE * coef + SGREEN * coef / 2 + SRED * coef / 3;
	else if (ant % 3 == 1)
		c = SBLUE * coef / 3 + SGREEN * coef + SRED * coef / 2;
	else
		c = SBLUE * coef / 2 + SGREEN * coef / 3 + SRED * coef;
	c = (ant % 2 == 0) ? 0x888888 + (7 * c) / 15 : WHITE - (13 * c) / 15;
	(ant % 4 >= 2) ? c = (unsigned int)c ^ 0xFFFFFF : 0;
	if (first != 0)
		write(1, " ", 1);
	ft_rgbputstr("L", (unsigned int)c, 0);
	ft_rgbputstr(ft_itoa(ant + 1), (unsigned int)c, 0);
	ft_rgbputstr("-", 0xF4EEDB, 0);
	c = (farm->end == ants[ant]) ? 0xED4347 : 0xF4EEDB;
	ft_rgbputstr(farm->rooms[ants[ant]]->name, (unsigned int)c, 0);
}

void		drop_out(t_farm *farm)
{
	int		i;

	i = 0;
	while (i < farm->info->cursize && farm->info->tab[i])
		ft_putendl(farm->info->tab[i++]);
	write(1, "\n", 1);
}
