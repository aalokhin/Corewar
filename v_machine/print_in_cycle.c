/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_in_cycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <vlikhotk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 13:54:55 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/11/20 13:55:07 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	intro_print(t_flags *params, t_header bots[4], WINDOW *win)
{
	int i;

	i = 0;
	if ((*params).ncurses == 1)
		visual_init(&win);
	printf("%s\n", "Introducing contestants...");
	while (i < (*params).bots_quantity)
	{
		printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i + 1,
			bots[i].prog_size, bots[i].prog_name, bots[i].comment);
		i++;
	}
}

void	after_cycle(t_flags *params, t_header bots[4],
	t_cycle main_cycle, WINDOW *win)
{
	int i;

	i = 0;
	while (i < (*params).bots_quantity)
	{
		free(bots[i].exec_part);
		bots[i].exec_part = NULL;
		i++;
	}
	if ((*params).ncurses == 1)
	{
		print_winner(win, main_cycle);
		endwin();
	}
	else if (!(*params).ncurses && !main_cycle.processes)
		printf("Contestant %d, \"%s\", has won !\n",
			main_cycle.winner_id + 1, main_cycle.winner_name);
}

void	print_adv(t_cycle *main_cycle, t_proc *processes, t_flags *params,
	unsigned char *map)
{
	int j;

	j = 0;
	(*main_cycle).indexes[(*processes).current_position][1] = 0;
	if (((*params).v_verbosity >> 4) & 1 && (*main_cycle).shift > 0)
	{
		printf("ADV %d (0x%.4x -> 0x%.4x) ", (*main_cycle).shift,
			(*processes).current_position, (*main_cycle).shift +
			(*processes).current_position);
		while (j < (*main_cycle).shift)
		{
			printf("%.2x ", map[((*processes).current_position
			+ j) % MEM_SIZE]);
			j++;
		}
		printf("\n");
	}
	(*processes).current_position += (*main_cycle).shift;
}

int		external_cycle_pass(t_cycle *main_cycle, unsigned char *map,
	t_flags *params)
{
	/*if ((*params).ncurses == 1 && main_cycle.second_limit > 0)
		usleep((useconds_t)((int)1000000 / main_cycle.second_limit));
	else if ((*params).ncurses == 1 && main_cycle.second_limit <= 0)
		main_cycle.second_limit = 1;*/
	(*main_cycle).cycles++;
	if (((*params).d_dumps_memory > 0 && (*main_cycle).cycles ==
		(*params).d_dumps_memory))
	{
		print_dump(map);
		return (0);
	}
	return (1);
}

void	print_dump(unsigned char *map)
{
	int i;

	i = 0;
	printf("0x0000 : ");
	while (i < MEM_SIZE)
	{
		printf("%.2x ", map[i]);
		if (++i % 64 == 0 && i < MEM_SIZE)
			printf("\n%#.4x : ", i);
	}
	printf("\n");
}
