/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <vlikhotk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 14:59:01 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/11/16 14:29:03 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	vm_cycle(unsigned char *map, t_flags *params,
	t_header bots[MAX_PLAYERS])
{
	t_cycle		main_cycle;
	t_proc		*processes;

	WINDOW * win;
	win = NULL;
	main_cycle_init(&main_cycle, params);
	fill_start_map_id(&main_cycle, bots, params);
	processes = processes_init(params, bots, map);
	main_cycle.head_proc = processes;
	intro_print(params, bots, &win);
	start_cycle(map, params, &win, &main_cycle);
	after_cycle(params, bots, main_cycle, &win);
}

void	fill_start_map_id(t_cycle *main_cycle, t_header bots[MAX_PLAYERS],
	t_flags *params)
{
	unsigned int	k;

	(*params).i = 0;
	(*params).j = 0;
	k = 0;
	while ((*params).i < MEM_SIZE)
	{
		(*main_cycle).indexes[(*params).i][0] = 0;
		(*main_cycle).indexes[(*params).i++][1] = NO_CARETKA;
	}
	(*params).i = 0;
	while ((*params).i < MEM_SIZE && (*params).j < (*params).bots_quantity)
	{
		if ((unsigned int)(*params).i == bots[(*params).j].start_index)
		{
			(*main_cycle).indexes[(*params).i][1] = CARETKA;
			k = 0;
			while (k++ < bots[(*params).j].prog_size)
				(*main_cycle).indexes[(*params).i++][0] = (*params).j + 1;
			(*params).j++;
		}
		else
			(*params).i++;
	}
}

void	create_map(t_header bots[MAX_PLAYERS], t_flags *params)
{
	unsigned int			i;
	int						j;
	unsigned int			k;
	static unsigned char	map[MEM_SIZE];

	i = 0;
	j = 0;
	k = 0;
	ft_bzero(map, MEM_SIZE);
	while (i < MEM_SIZE && j < (*params).bots_quantity)
	{
		if (i == bots[j].start_index)
		{
			k = 0;
			while (k < bots[j].prog_size && i < MEM_SIZE)
				map[i++] = bots[j].exec_part[k++];
			j++;
		}
		else
			i++;
	}
	vm_cycle(map, params, bots);
}

void	print_usage(void)
{
	char *octos;

	octos = "##########################################################";
	ft_printf("%s", "Usage: ./corewar [-dump N -v N");
	ft_printf("%s\n", " -n N | -nc] [-a] <champion1.cor> <...>");
	ft_printf("%6s", "-a");
	ft_printf("%58s\n", ": Prints output from \"aff\" (Default is to hide it)");
	ft_printf("%s%s\n", "#### TEXT OUTPUT MODE ", octos);
	ft_printf("%11s%43s\n",
		"-dump N", ": Dumps memory after N cycles then exits");
	ft_printf("%26s", "-v N      : Verbosity ");
	ft_printf("%s\n", "levels, can be added together to enable several");
	ft_printf("%43s%32s\n", "- 0 : Show only essentials\n", "- 1 : Show lives");
	ft_printf("%33s\n", "- 2 : Show cycles");
	ft_printf("%67s\n", "- 4 : Show operations (Params are NOT litteral ...)");
	ft_printf("%33s\n", "- 8 : Show deaths");
	ft_printf("%59s\n", "- 16 : Show PC movements (Except for jumps)");
	ft_printf("%s%s\n", "#### NCURSES OUTPUT MODE ", octos);
	ft_printf("%36s\n", "-nc        : Ncurses output mode");
	ft_printf("%s%.22s\n", octos, octos);
}

int		main(int argc, char **argv)
{
	int				fd;
	t_flags			params;
	static t_header	bots[MAX_PLAYERS];

	fd = 0;
	if (argc == 1)
	{
		print_usage();
		return (0);
	}
	if (CHAMP_MAX_SIZE > MEM_SIZE || MEM_SIZE < 16)
	{
		ft_printf("%s\n", "Error: Incorrect const values");
		return (0);
	}
	params_init(&params);
	if (check_flags_core(argc, argv, &params) <= 0)
		exit(0);
	params.j = 0;
	init_bots(bots);
	if (!read_bots(&params, fd, bots))
	{
		//while (1)
			//;
		exit(0);
	}
	//while (1)
			//;
}
