#include "../corewar.h"

void processes_add(t_proc **head, unsigned char *map, t_cycle *main_cycle, int index, int cur_proc)
{
	t_proc *tmp;
	t_proc *parent;
	t_proc *tail;
	int j;

	j = 0;
	tmp = NULL;
	parent = NULL;
	tail = *head;
	(*main_cycle).processes++;
	while (tail && (*tail).id != cur_proc)
		tail = tail->next;
	parent = tail;
	tmp = (t_proc *)malloc(sizeof(t_proc));
	if ((**head).id == 0)
		tmp->id = (*main_cycle).start_bots;
	else
		tmp->id = (**head).real_id + 1;
	tmp->real_id = (**head).real_id + 1;
	tmp->name = (*parent).name;
	tmp->current_position = index;
	tmp->carry = (*parent).carry;
	if ((*parent).parent_nbr == -1)
		tmp->parent_nbr = (*parent).real_id;
	else
		tmp->parent_nbr = (*parent).parent_nbr;
	tmp->if_live = 1;
	tmp->cmd = map[tmp->current_position];
	//(*main_cycle).indexes[index][0] = tmp->parent_nbr + 1;
	(*main_cycle).indexes[index][1] = 1;
	if (tmp->cmd >= 1 && tmp->cmd <= 16)
		tmp->cycles_wait = op_tab[tmp->cmd - 1].cycles_wait;
	else
		tmp->cycles_wait = 1;
	tmp->last_live_cycle = 0;
	tmp->child_proc_lives = 0;
	tmp->live_cycle = (*parent).live_cycle + 1;
	clear_argv_arr(tmp);
	while (j < REG_NUMBER)
	{
		tmp->regs[j] = (*parent).regs[j];
		j++;
	}
	tmp->next = *head;
	*head = tmp;
	(*main_cycle).head_proc = *head;
}

int find_arg_index(t_proc *processes, int target)
{
	int i;

	i = 0;
	while(i < 3 && (*processes).argv[i][0] != target)
		i++;
	return (i);
}

int check_if_lives(t_cycle *main_cycle, t_flags *params)
{
	int res;
	t_proc *tmp;
	t_proc *tmp2;

	res = 0;
	tmp = (*main_cycle).head_proc;
	tmp2 = (*main_cycle).head_proc;
	while (tmp)
	{
		if ((*tmp).last_live_cycle > (*main_cycle).current_winner)
		{
			(*main_cycle).current_winner = (*tmp).last_live_cycle;
			if ((*tmp).parent_nbr == -1)
				(*main_cycle).winner_id = (*tmp).id;
			else
				(*main_cycle).winner_id = (*tmp).parent_nbr;
			(*main_cycle).winner_name = (*tmp).name;
		}
		if ((*tmp).lives == 0 && (*tmp).if_live && (*tmp).live_cycle > (*main_cycle).cycle_die)
		{
			(*tmp).if_live = 0;
			(*main_cycle).processes--;
			(*tmp).lives = 0;
			(*main_cycle).indexes[(*tmp).current_position][1] = 0;
			if (((*params).v_verbosity >> 3) & 1)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
					(*tmp).id + 1, (*tmp).live_cycle - 1, (*main_cycle).cycle_die);
		}
		else
		{
			res += (*tmp).lives;
			(*tmp).lives = 0;
		}
		tmp = tmp->next;
	}
	return (res);
}

void fill_start_map_id(t_cycle *main_cycle, header_t bots[4], t_flags *params)
{
	unsigned int i;
	int j;
	unsigned int k;

	i = 0;
	j = 0;
	k = 0;
	while (i < MEM_SIZE)
	{

		(*main_cycle).indexes[i][0] = 0;
		(*main_cycle).indexes[i][1] = 0;
		i++;
	}
	i = 0;
	while (i < MEM_SIZE && j < (*params).bots_quantity)
	{
		if (i == bots[j].start_index)
		{
			(*main_cycle).indexes[i][1] = 1;
			k = 0;
			while (k < bots[j].prog_size)
			{
				(*main_cycle).indexes[i][0] = j + 1;
				i++;
				k++;
			}
			j++;
		}
		i++;
	}
}

void print_dump(unsigned char *map)
{
	int		i;

	i = 0;
	ft_printf("0x0000 : ");
	while (i < MEM_SIZE)
	{
		ft_printf("%.2x ", map[i]);
		if (++i % 64 == 0 && i < MEM_SIZE)
			ft_printf("\n%#.4x : ", i);
	}
	ft_printf("\n");
}

void vm_cycle(unsigned char *map, t_flags *params, header_t bots[4])
{
	int i;
	t_cycle main_cycle;
	t_proc *processes;
	int id_counter;
	WINDOW *win;
	int cycle_counter;
	int res;
	int j;

	j = 0;
	cycle_counter = 0;
	win = NULL;
	i = 0;
	processes = NULL;
	id_counter = 0;
	res = 0;
	main_cycle_init(&main_cycle, params);
	fill_start_map_id(&main_cycle, bots, params);
	processes = processes_init(params, bots, map);
	main_cycle.head_proc = processes;
	if ((*params).ncurses == 1)
		visual_init(&win);
	ft_printf("%s\n", "Introducing contestants...");
	
	while (i < (*params).bots_quantity)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i + 1, bots[i].prog_size, bots[i].prog_name, bots[i].comment);
		i++;
	}
	i = 0;
	while (main_cycle.processes > 0)
	{
		//cycle_counter++;
		if (((*params).v_verbosity >> 1) & 1)
			ft_printf("%s%d\n", "It is now cycle ", main_cycle.cycles + 1);
		
		i = 0;
		processes = main_cycle.head_proc;
		if ((*params).ncurses == 1)
			map_to_screen(map, &main_cycle, params, main_cycle.head_proc, win);


		while (processes)
		{
			if ((*processes).if_live && (*processes).cmd >= 1 && (*processes).cmd <= 16 && (*processes).cycles_wait == 1)
			{
				if (op_tab[(*processes).cmd - 1].codage)
				{
					id_counter = ((*processes).current_position + 1 + MEM_SIZE) % MEM_SIZE;
					take_args(map[id_counter], processes);
					get_args_values(processes, map, &id_counter);
				}
				else
				{
					id_counter = (*processes).current_position;
					(*processes).argv[0][0] = DIR_CODE;
					get_arg_vals[(*processes).argv[0][0] - 1](processes, map, 0, &id_counter);
				}

				if ((*processes).cmd == 1 || (*processes).cmd == 12 || (*processes).cmd == 15)
					res = instruct[(*processes).cmd - 1](main_cycle.head_proc, (*processes).id, &main_cycle, map);
				else if ((*processes).cmd != 16 || ((*processes).cmd == 16 && (*params).a_aff))
					res = instruct[(*processes).cmd - 1](processes, (*processes).id, &main_cycle, map);
				else if ((*processes).cmd == 16 && !(*params).a_aff)
					res = 0;
				if (((*processes).cmd != 9 && res == 1) || ((*processes).cmd == 9 && (*processes).carry == 0) ||
					(*processes).cmd == 11 || (*processes).cmd == 14 || (*processes).cmd == 6 || (*processes).cmd == 7
					 || (*processes).cmd == 4 || (*processes).cmd == 10)
				{
					main_cycle.indexes[((*processes).current_position + MEM_SIZE) % MEM_SIZE][1] = 0;
					if ((((*params).v_verbosity >> 4) & 1) && ((*processes).cmd != 9 || ((*processes).cmd == 9 && (*processes).carry == 0)))
					{
						ft_printf("ADV %d (0x%.4x -> 0x%.4x) ", id_counter + 1 - (*processes).current_position, (*processes).current_position, id_counter + 1);
						j = 0;
						while (j < id_counter + 1 - (*processes).current_position)
						{
							ft_printf("%.2x ", map[((*processes).current_position + j) % MEM_SIZE]);
							j++;
						}
						ft_printf("\n");
					}
					(*processes).current_position = id_counter + 1;
				}
				else if ((*processes).cmd != 9 && res == 0)
				{
					main_cycle.indexes[(*processes).current_position][1] = 0;
					if (((*params).v_verbosity >> 4) & 1)
					{
						ft_printf("ADV %d (0x%.4x -> 0x%.4x) ", 2, (*processes).current_position, 2 + (*processes).current_position);
						j = 0;
						while (j < 2)
						{
							ft_printf("%.2x ", map[((*processes).current_position + j) % MEM_SIZE]);
							j++;
						}
						ft_printf("\n");
					}
					(*processes).current_position += 2;
				}
				//res = -1;
				(*processes).current_position = ((*processes).current_position + MEM_SIZE) % MEM_SIZE;
				(*processes).cmd = map[(*processes).current_position];
				if ((*processes).cmd >= 1 && (*processes).cmd <= 16)
					(*processes).cycles_wait = op_tab[(*processes).cmd - 1].cycles_wait;
				else
					(*processes).cycles_wait = 1;
				/*if ((*processes).parent_nbr == -1)
					main_cycle.indexes[(*processes).current_position][0] = (*processes).real_id + 1;
				else
					main_cycle.indexes[(*processes).current_position ][0] = (*processes).parent_nbr + 1;*/
				main_cycle.indexes[(*processes).current_position][1] = 1;
				clear_argv_arr(processes);
			}
			else if ((*processes).if_live && (*processes).cmd >= 1 && (*processes).cmd <= 16 && (*processes).cycles_wait > 1)
				(*processes).cycles_wait--;
			else if ((*processes).if_live)
			{
				main_cycle.indexes[(*processes).current_position][1] = 0;
				(*processes).current_position++;
				(*processes).current_position = ((*processes).current_position + MEM_SIZE) % MEM_SIZE;
				(*processes).cmd = map[(*processes).current_position];
				if ((*processes).cmd >= 1 && (*processes).cmd <= 16)
					(*processes).cycles_wait = op_tab[(*processes).cmd - 1].cycles_wait;
				else
					(*processes).cycles_wait = 1;
				/*if ((*processes).parent_nbr == -1)
					main_cycle.indexes[(*processes).current_position][0] = (*processes).real_id + 1;
				else
					main_cycle.indexes[(*processes).current_position][0] = (*processes).parent_nbr + 1;*/
				main_cycle.indexes[(*processes).current_position][1] = 1;
			}			
			(*processes).live_cycle++;
			processes = processes->next;
			i++;
		}
		if (++cycle_counter == main_cycle.cycle_die || main_cycle.cycle_die < 0)
		{
			cycle_counter = 0;
			if (check_if_lives(&main_cycle, params) >= NBR_LIVE || main_cycle.checks_if_die == 0)
			{
				main_cycle.cycle_die -= CYCLE_DELTA;
				main_cycle.checks_if_die = MAX_CHECKS;
				if (((*params).v_verbosity >> 1) & 1)
					ft_printf("%s%d\n", "Cycle to die is now ", main_cycle.cycle_die);
			}
			main_cycle.checks_if_die--;
		}
		//main_cycle.prev_processes = main_cycle.processes;
		/*if (main_cycle.second_limit > 0)
			usleep((useconds_t)((int)1000000 / main_cycle.second_limit));
		else
			main_cycle.second_limit = 1;*/
		main_cycle.cycles++;
		if (((*params).d_dumps_memory > 0 && main_cycle.cycles == (*params).d_dumps_memory))
		{
			print_dump(map);
			break ;
		}
	}
	if ((*params).ncurses == 1)
	{
		print_winner(win, main_cycle);
		endwin();
	}
	else if ((*params).d_dumps_memory <= 0)
		ft_printf("Contestant %d, \"%s\", has won !\n", main_cycle.winner_id + 1, main_cycle.winner_name);
}