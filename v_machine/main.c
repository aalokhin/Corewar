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
			while (k < bots[j].prog_size)
			{
				map[i] = bots[j].exec_part[k];
				i++;
				k++;
			}
			j++;
		}
		i++;
	}
	vm_cycle(map, params, bots);
}

void	print_usage(void)
{
	char *octos;

	octos = "##########################################################";
	ft_printf("%s", "Usage: ./corewar [-d N -v N");
	ft_printf("%s\n", "| -n N] [-a] <champion1.cor> <...>");
	ft_printf("%6s", "-a");
	ft_printf("%58s\n", ": Prints output from \"aff\" (Default is to hide it)");
	ft_printf("%s%s\n", "#### TEXT OUTPUT MODE ", octos);
	ft_printf("%8s%46s\n", "-d N", ": Dumps memory after N cycles then exits");
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

int		check_flags_with_nbr(char **argv, int argc, t_flags *params)
{
	if (ft_strcmp(argv[(*params).i], "-d") == 0 && (*params).i + 1 < argc)
	{
		(*params).d_dumps_memory = ft_atoi(argv[(*params).i + 1]);
		(*params).i += 2;
		return (1);
	}
	else if (ft_strcmp(argv[(*params).i], "-v") == 0 && (*params).i + 1 < argc)
	{
		(*params).v_verbosity = ft_atoi(argv[(*params).i + 1]);
		(*params).i += 2;
		return (1);
	}
	else if (ft_strcmp(argv[(*params).i], "-n") == 0 && (*params).j < MAX_PLAYERS
		&& (*params).i + 1 < argc)
	{
		(*params).pl_nbr[(*params).j][0] = 1;
		(*params).pl_nbr[(*params).j][1] = ft_atoi(argv[(*params).i + 1]);
		(*params).i += 2;
		return (1);
	}
	return (0);
}

int		check_flags_core(int argc, char **argv, t_flags *params)
{
	while ((*params).i < argc)
	{
		if (ft_strcmp(argv[(*params).i], "-a") == 0)
			(*params).a_aff = 1;
		else if (check_flags_with_nbr(argv, argc, params))
			continue ;
		else if (ft_strcmp(argv[(*params).i], "-nc") == 0)
			(*params).ncurses = 1;
		else if (ft_strchr(argv[(*params).i], '.') && ft_strcmp(&
		(argv[(*params).i][ft_strlen(argv[(*params).i]) - 4]), ".cor") == 0)
		{
			if ((*params).bots_quantity == MAX_PLAYERS)
				return (0);
			(*params).j++;
			(*params).players[(*params).bots_quantity++] = argv[(*params).i];
		}
		else
			return (-1);
		(*params).i++;
	}
	return (1);
}

int		main(int argc, char **argv)
{
	int				fd;
	t_flags			params;
	static t_header	bots[MAX_PLAYERS];
	int				res;

	res = 0;
	fd = 0;
	if (argc == 1)
	{
		print_usage();
		return (0);
	}
	params_init(&params);
	res = check_flags_core(argc, argv, &params);
	if (res <= 0)
	{
		if (res == 0)
			ft_printf("%s\n", "Too many champions");
		if (res < 0)
			ft_printf("%s %s\n", "Can't read source file", argv[params.i]);
		exit(0);
	}
	init_bots(bots);
	if (!read_bots(&params, fd, bots))
		exit(0);
	create_map(bots, &params);
}
